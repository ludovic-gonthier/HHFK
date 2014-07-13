<?hh //strict
namespace HHFK\Service;

use HHFK\Config;

use HHFK\Exception\HHFKException;
use HHFK\Exception\Oop\ClassNotFoundException;
use HHFK\Exception\NotRegisteredException;

final class Service<T>
{
    const string OPEN_GLOBAL_VARIABLE = "{{",
                 CLOSE_GLOBAL_VARIABLE = "}}",
                 OPEN_LOCAL_VARIABLE = "{",
                 CLOSE_LOCAL_VARIABLE = "}";

    /**
     * Private constructor because it's a static class
     */
    private function __construct()
    {
    }

    /**
     * Fille the provider with the given configuration array
     *
     * @param  array  $configuration
     *
     */
    public static function prepare(array $configuration) : void
    {
        $parameters = (array_key_exists('parameters', $configuration) ? $configuration['parameters'] : array());
        foreach ($configuration['services'] as $name => &$service) {
            if (!array_key_exists('class', $service)) {
                ##TODO Correct Exception
                throw new HHFKException("Cannot register a service without a 'class' provided in the configuration file.");
            }
            $service['class'] = self::_replaceVariables($service['class'], $parameters);
            if (array_key_exists('arguments', $service)) {
                foreach ($service['arguments'] as &$arg) {
                    $arg = self::_replaceVariables($arg, $parameters);
                }
            } else {
                $service['arguments'] = array();
            }
            self::$_waiting->add(Pair{$name, $service});
        }
    }

    public static function boot()
    {
        while (self::$_waiting->count() > 0) {
            $popped = self::$_waiting->pop();

            self::register($popped[0], $popped[1]['class'], $popped[1]['arguments']);
        }
        self::$_booted = true;
    }

    private static function _parseConfiguration(string $string, Pair<string, string> $delimiter, (function (string) : string) $replacer) : string
    {
        $initialString = $string;
        $open = mb_strpos($string, $delimiter->at(0));
        while ($open !== false) {
            $close = mb_strpos($string, $delimiter->at(1));
            if ($close === false) {
                throw new BadPatternFormatException("Bad pattern format: mismatched closing bracket in the pattern: '" . $initialString . "'");
            }
            $extract = mb_substr($string, $open + mb_strlen($delimiter->at(0)),  $close - $open - mb_strlen($delimiter->at(1)));
            $replace = $replacer($extract);
            $string = mb_substr($string, 0, $open) . $replace . mb_substr($string, $close + mb_strlen($delimiter->at(1)));
            // loop
            $open = mb_strpos($string, $delimiter->at(0));
        }
        return $string;
    }

    /**
     * Replace configuration variable of the given value
     *
     * @param  string $value
     * @param  array  $parameters
     *
     * @return The correctly replaced value
     */
    private static function _replaceVariables(string $value, array $parameters) : string
    {
        $localPair = Pair{self::OPEN_LOCAL_VARIABLE, self::CLOSE_LOCAL_VARIABLE};
        $globalPair = Pair{self::OPEN_GLOBAL_VARIABLE, self::CLOSE_GLOBAL_VARIABLE};

        $value = self::_parseConfiguration($value, $globalPair, $key ==> {
            if (Config::exists($key)) {
                return Config::get($key);
            }
            ##TODO Correct Exception
            throw new \Exception("Trying to fetch an unset global variable: '" . $key ."'");
        });
        $value = self::_parseConfiguration($value, $localPair, $key ==> {
            if (array_key_exists($key, $parameters)) {
                return $parameters[$key];
            }
            ##TODO Correct Exception
            throw new \Exception("Trying to fetch an unset local parametr: '" . $key ."'");
        });
        return $value;
    }

    private static function _checkCorrectParameter(?\ReflectionMethod $constructor, array $parameters) : bool
    {
        if ($constructor === null) {
            return true;
        }
        ## TODO check for default parameter!!!
        if (count($constructor->getParameters()) !== count($parameters)) {
            return false;
        }
        return true;
    }
    /**
     * Register a service in the provider
     *
     * @param  Service $service
     */
    public static function register(string $name, string $class, array $parameters = array()) :void
    {
        if (class_exists($class) === false) {
            throw new ClassNotFoundException("'". $class . "': no such class declared.");
        }
        foreach ($parameters as $label => $parameter) {
            // If a parameter is a registered class
            if (class_exists($parameter) === true) {
                Service::get("logger")->warn("Can't pass a non-service class to as Service.", $parameter);
                continue;
            }
            ##TODO take care of recursive Servie Registration
            if (self::exists($parameter)) {// instance of Service
                $parameters[$label] = self::get($parameter);
            }
            else {
                $pair = null;
                foreach (self::$_waiting as $service) {
                    if ($service[0] === $parameter){
                        $pair = $service;
                        break;
                    }
                }
                if (!isset($pair)) {
                    continue;
                }
                if (array_key_exists('delayed', $pair[1])) {
                    ##TODO Correct Exception
                    throw new HHFKException("Cycle service inclusion");
                }
                self::$_waiting->removeKey(self::$_waiting->linearSearch($pair));
                self::$_waiting->add(Pair{$name, array(
                        'class' => $class,
                        'arguments' => $parameters,
                        'delayed' => true
                    )
                });
            }
        }
        $reflect = new \ReflectionClass($class);
        if (self::_checkCorrectParameter($reflect->getConstructor(), $parameters) === false) {
            ##TODO correct exception
            throw new HHFKException("Wrong parameters number");
        }
        self::$_services[$name] = $reflect->newInstanceArgs($parameters);
    }
    /**
     * Return the registered service in the provider
     * @return ImmMap<string, Service>
     */
    public static function registered() :ImmMap<string, T>
    {
        return self::$_services->toImmMap();
    }
    /**
     * Check if a service exists
     *
     * @param  string $serviceName
     * @return bool
     */
    public static function exists(string $serviceName) : bool
    {
        return self::$_services->contains($serviceName);
    }
    /**
     * Fetch a registered service
     *
     * @param  string $serviceName
     * @return mixed Instance of the service
     * @throws HHFKException If the service is not registered
     */
    public static function get(string $serviceName) : T
    {
        $service = self::$_services->get($serviceName);
        if ($service === null) {
            throw new NotRegisteredException("Service '" . $serviceName . "' requested is not registered");
        }
        return $service;
    }

    private static bool $_booted = false;
    private static Map<string, T> $_services = Map{};
    private static Vector<Pair<string, array>> $_waiting = Vector{};
}