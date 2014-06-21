<?hh //strict
namespace HHFK\Service;

use HHFK\Service\Service;
use HHFK\Exception\HHFKException;
use HHFK\Exception\Oop\ClassNotFoundException;
use HHFK\Exception\NotRegisteredException;


## TODO pass service provider to Controller as attributes $_services;
class ServiceProvider<T>
{
	const string OPEN_GLOBAL_VARIABLE = "{{",
				 CLOSE_GLOBAL_VARIABLE = "}}",
				 OPEN_LOCAL_VARIABLE = "{",
				 CLOSE_LOCAL_VARIABLE = "}";

	protected function __construct()
	{
		$this->_services = new Map();
		$this->_preparedService = new Vector();
	}

	/**
	 * Fille the provider with the given configuration array
	 * 
	 * @param  array  $configuration
	 * 
	 */
	public function prepare(array $configuration): void
	{
		$parameters = (array_key_exists('parameters', $configuration) ? $configuration['parameters'] : array());
		foreach ($configuration['services'] as $name => &$service) {
			if (!array_key_exists('class', $service)) {
				##TODO Correct Exception
				throw new HHFKException("Cannot register a service without a 'class' provided in the configuration file.");
			}
			$service['class'] = $this->_replaceVariables($service['class'], $parameters);
			if (array_key_exists('arguments', $service)) {
				foreach ($service['arguments'] as &$arg) {
					$arg = $this->_replaceVariables($arg, $parameters);
				}
			} else {
				$service['arguments'] = array();
			}
			$this->_preparedService->add(Pair{$name, $service});
		}
	}

	public function boot()
	{
		while ($this->_preparedService->count() > 0) {
			$popped = $this->_preparedService->pop();

			$this->register($popped[0], $popped[1]['class'], $popped[1]['arguments']);
		}
	}

	/**
	 * Replace configuration variable of the given value
	 * 
	 * @param  string $value
	 * @param  array  $parameters
	 * 
	 * @return The correctly replaced value
	 */
	##TODO Function as Class => Used by router too
	##TODO Replace global variables
	private function _replaceVariables(string $value, array $parameters): string
	{
		$initialPattern = $value; // For correct pattern in exception
        $openBracket = strpos($value, self::OPEN_LOCAL_VARIABLE);
        while ($openBracket !== false) {
            $closeBracket = strpos($value, self::CLOSE_LOCAL_VARIABLE);
            if ($closeBracket === false) {
                throw new BadPatternFormatException("Bad pattern format: mismatched closing bracket in the pattern: '" . $initialPattern . "'");
            }
            $key = substr($value, $openBracket + 1,  $closeBracket - $openBracket - 1);
            if (array_key_exists($key, $parameters)) {
            	$value = substr($value, 0, $openBracket) . $parameters[$key] . substr($value, $closeBracket + 1);
            }

            $openBracket = strpos($value, self::OPEN_LOCAL_VARIABLE);
        }
        return $value;
	}

	/**
	 * Register a service in the provider
	 * 
	 * @param  Service $service
	 */
	public function register(string $name, string $class, array $parameters = array()):void
	{
		foreach ($parameters as $label => $parameter) {
			// If a parameter is a registered class
			if (class_exists($parameter) === true) {
				$parameters[$label] = new $parameter();
				continue;
			}
			##TODO take care of recursive Servie Registration
			if ($this->serviceExists($parameter)) {// instance of Service
				$parameters[$label] = $this->get($parameter);
			} 
			else {
				$pair = null;
				foreach ($this->_preparedService as $service) {
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
				$this->_preparedService->removeKey($this->_preparedService->linearSearch($pair));
				$this->_preparedService->add(Pair{$name, array(
					'class' => $class,
					'arguments' => $parameters,
					'delayed' => true
				)
				});
			}
		}
		if (class_exists($class) === false) {
			throw new ClassNotFoundException("'". $class . "': no such class declared.");
		}
		$reflect = new \Reflectionclass($class);
		$this->_services[$name] = $reflect->newInstanceArgs($parameters);
	}
	/**
	 * Return the registered service in the provider
	 * @return ImmMap<string, Service>
	 */
	public function registered():ImmMap<string, T>
	{
		return $this->_services->toImmMap();
	}
	/**
	 * Check if a service exists
	 * 
	 * @param  string $serviceName
	 * @return bool
	 */
	public function serviceExists(string $serviceName): bool
	{
		return $this->_services->contains($serviceName);
	}
	/**
	 * Fetch a registered service
	 * 
	 * @param  string $serviceName
	 * @return mixed Instance of the service
	 * @throws HHFKException If the service is not registered
	 */
	public function get(string $serviceName): T
	{
		$service = $this->_services->get($serviceName);
		if ($service === null) {
			throw new NotRegisteredException("Service '" . $serviceName . "' requested is not registered");
		}
		return $service;
	}

	/**
	 * Return an instance of the ServiceProvider
	 * @return ServiceProvider
	 */
	public static function getInstance(): ?this
	{
		if (!isset(self::$_instance)) {
			self::$_instance = new static();
		}
		return self::$_instance;
	}

	protected Map<string, T> $_services;
	private Vector<Pair<string, array>> $_preparedService;
	private static ?ServiceProvider $_instance = null;
}