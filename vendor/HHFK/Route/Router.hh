<?hh
namespace HHFK\Route;

use HHFK\Exception\HHFKException;
use HHFK\Http\Response;

class Router{
    public static function provide(string $pattern, string $controller): Route
    {
        $route = new Route($pattern, $controller);
        if (!isset(self::$_routes)){
            self::$_routes = new Vector<Route>();
        }
        self::$_routes[] = $route;
        return $route;
    }

    public static function provided(): Vector<Route>
    {
        return self::$_routes;
    }

    public static function resolve(Url $url): Response
    {
        ##TODO
        // Fetch the correct Route
        $route = self::$_routes->get(0);

        // Fetch the route controller
        $controller = new ($route->getController());
        // Attach route and url to request
        $return = call_user_func_array(array($controller, $route->getAction()),
                                       $route->getDatas()->toArray());
        if ($return === false){
            ##TODO
            // Handle Error
        }
        return $return;
    }
    
    private static Vector<Route> $_routes;
}