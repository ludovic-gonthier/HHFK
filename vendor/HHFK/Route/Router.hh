<?hh
namespace HHFK\Route;

use HHFK\Exception\NotFoundException;
use HHFK\Http\Response;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;


##TODO class as Service
## Configuration with INI Files
class Router{
    const string OPEN_BRACKET = "{";
    const string CLOSE_BRACKET = "}";
    const string REGEXP = "[A-Za-z0-9+_-]*";

    protected function __construct()
    {
        $this->_routes = new Map<string, Route>;
    }

    public function provide(string $pattern, string $controller): Route
    {
        $route = new Route($pattern, $controller);
        if (!isset($this->_routes)){
        }
        $this->_routes[$pattern] = $route;
        return $route;
    }

    public function provided(): Vector<Route>
    {
        return $this->_routes;
    }

    public function resolve(Url $url): Response
    {
        $route = $this->fetchRoute($url);
        $controller = new ($route->getController());
        ##TODO Attach route and url to request
        ##TODO Check if authorised request

        ##TODO : ServiceProvider => store logger
        $logger = new Logger(static::class);
        $logger->pushHandler(new StreamHandler('/var/log/lgo/info.log', Logger::INFO));
        $logger->addInfo($class . "->" . $route->getAction());

        $handler = array($controller, $route->getAction());
        if (is_callable($handler) === false) {
            ##TODO Correct Exception
            $logger->addInfo($class . "->" . $route->getAction() . " FAILED");
            throw new Exception("Call to an undefined method '" . $route->getAction() . "' in the controller '" . $controller . "'");
        }
        return call_user_func_array($handler, $route->getDatas()->toArray());
    }

    private function replaceVariableInPattern(string &$pattern)
    {
        $openBracket = strpos($pattern, self::OPEN_BRACKET);
        while ($openBracket !== false) {
            $closeBracket = strpos($pattern, self::CLOSE_BRACKET);
            if ($closeBracket === false) {
                ## TODO correct  Exception
                throw new \Exception("Could not find closing bracket for the pattern: '" . $pattern . "'");
            }
            $regexp = "(?<" . substr($pattern, $openBracket + 1,  $closeBracket - $openBracket - 1) . ">" . self::REGEXP . ")";
            $pattern = substr($pattern, 0, $openBracket) . $regexp . substr($pattern, $closeBracket + 1);

            $openBracket = strpos($pattern, self::OPEN_BRACKET);
        }
    }

    private function fetchRoute(Url $url): Route
    {
        $route = $this->_routes->get($url->getPath());
        if ($route !== null) {
            return $route;
        }

        foreach ($this->_routes as $pattern => $route) {
            $this->replaceVariableInPattern($pattern);
            $regexp = "/^" . str_replace('/', "\/", $pattern) . "$/";
            if (preg_match($regexp, $url->getPath(), $match)) {
                foreach ($match as $key => $value) {
                    if (is_int($key)) {
                        continue;
                    }
                    $route->addData($key, $value);
                }
                return $route;
            }
        }
        throw new NotFoundException("No route match the pattern '" . $url->getPath() . "'");
    }

    public static function getInstance()
    {
        if (!isset(static::$_instance)){
            self::$_instance = new self();
        }
        return self::$_instance;
    }
    protected static Router $_instance = null;
    
    private Map<string, Route> $_routes;
}