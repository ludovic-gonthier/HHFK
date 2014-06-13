<?hh
namespace HHFK\Route;

use HHFK\Exception\NotFoundException;
use HHFK\Http\Response;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;


##TODO class as Service
## Configuration with arrays
class Router{
    const string OPEN_BRACKET = "{";
    const string CLOSE_BRACKET = "}";
    const string REGEXP_SUBSTITUTION = "([a-z0-9+_-]*)";

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
        // Attach route and url to request

        ##TODO : ServiceProvider => store logger
        $logger = new Logger(static::class);
        $logger->pushHandler(new StreamHandler('/var/log/lgo/info.log', Logger::INFO));
        $logger->addInfo($class . "->" . $route->getAction());

        $return = call_user_func_array(array($controller, $route->getAction()),
                                       $route->getDatas()->toArray());
        if ($return === false){
            ##TODO : Handle error
            $logger->addInfo($class . "->" . $route->getAction() . " FAILED");
        }
        return $return;
    }

    private function fetchRoute(Url $url): Route
    {
        $route = $this->_routes->get($url->getPath());
        // route directly found
        if ($route !== null)
            return $route;
        ## TODO : Test for route with multiples {}
        foreach ($this->_routes as $pattern => $route){
            $openBracket = strpos($pattern, self::OPEN_BRACKET);
            $variable = null;
            while ($openBracket !== false){
                $closeBracket = strpos($pattern, self::CLOSE_BRACKET);
                if ($closeBracket === false) {
                    ## TODO correct  Exception
                    throw new \Exception("Could not find closing bracket for the pattern: '" . $pattern . "'");
                }
                $tmpPattern = substr($pattern, 0, $openBracket);
                $variable = substr($pattern, $openBracket + 1,  $closeBracket - $openBracket - 1);
                $pattern = $tmpPattern . self::REGEXP_SUBSTITUTION . substr($pattern, $closeBracket + 1);
                $openBracket = strpos(self::OPEN_BRACKET, $pattern);
            }
            $regexp = "/^" . str_replace('/', "\/", $pattern) . "$/";
            if (preg_match($regexp, $url->getPath(), $match)) {$
                $route->addData($variable, $match[1]);
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