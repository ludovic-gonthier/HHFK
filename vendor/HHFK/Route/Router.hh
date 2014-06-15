<?hh
namespace HHFK\Route;

use HHFK\Exception\NotFoundException;
use HHFK\Http\Response;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;

class Router{
    const string OPEN_BRACKET = "{";
    const string CLOSE_BRACKET = "}";
    const string REGEXP = "[A-Za-z0-9+_-]*";

    public function __construct()
    {
        $this->_routes = new Map<string, Route>;
    }

    /**
     * Provide the router with the route fetched from INI files
     * 
     * @param  array  $configuration Array returned from INI file parsing
     * @throws Exception If no pattern given in the configuration array
     * @throws Exception If no controller given in the configuration array
     */
    public function prepare(array $configuration): void
    {
        foreach ($configuration as $name => $parameters) {
            if (!array_key_exists("pattern", $parameters)) {
                ## TODO Correct Exception
                throw new \Exception("Route not correctly formatted: no pattern set");
            }
            if (!array_key_exists("controller", $parameters)) {
                ## TODO Correct Exception
                throw new \Exception("Route not correctly formatted: no controller provided");
            }
            $route = new Route($parameters["pattern"], $parameters["controller"]);
            $route->setName($name);
            if (array_key_exists("action", $parameters)) {
                $route->setAction($parameters["action"]);
            }
            if (array_key_exists("options", $parameters) && array_key_exists("method", $parameters["options"])) {
                ## TODO Set multiple authorised request for a route
                $route->setRequestType($parameters["options"]["method"]);
            }
            if (array_key_exists("datas", $parameters)) {
                foreach ($parameters["datas"] as $key => $value) {
                    $route->addData($key, $value);
                }
            }
            $this->_routes[$route->getPattern()] = $route;
        }
    }

    /**
     * Return the known route by the router
     * 
     * @return Map<string, Route> The map containing the known route
     */
    public function provided(): Map<string, Route>
    {
        return $this->_routes;
    }

    /**
     * Resolve a route
     * Find the correct route corresponding to the URL
     * Call the controller for the route action, with the route datas
     * 
     * @param  Url    $url Url to resolve
     * 
     * @return Response The response of the route call
     * @throws Exception If trying to call an unknown controller's action
     */
    public function resolve(Url $url): Response
    {
        $route = $this->fetchRoute($url);
        $controller = new ($route->getController());
        ## TODO Attach route and url to request
        ## TODO Check if authorised request

        ## TODO : ServiceProvider => store logger
        $logger = new Logger(static::class);
        $logger->pushHandler(new StreamHandler('/var/log/lgo/info.log', Logger::INFO));
        $logger->addInfo($class . "->" . $route->getAction());

        $handler = array($controller, $route->getAction());
        if (is_callable($handler) === false) {
            ## TODO Correct Exception
            $logger->addInfo($class . "->" . $route->getAction() . " FAILED");
            throw new \Exception("Call to an undefined method '" . $route->getAction() . "' in the controller '" . $controller . "'");
        }
        return call_user_func_array($handler, $route->getDatas()->toArray());
    }

    /**
     * Resolve route with variable parameter's in, and format 
     * the pattern for regexp
     * 
     * @param  string $pattern Pattern of the URL
     * e.g: /user/{user_id}/
     * @throws Exception If Pattern not correctly formatted
     */
    private function replaceVariableInPattern(string &$pattern): void
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

    /**
     * Find the correct route for the given URL
     * 
     * @param  Url    $url
     * @return Route The found route
     * @throws NotFoundException If no route found
     */
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
    
    private Map<string, Route> $_routes;
}