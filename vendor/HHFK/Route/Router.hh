<?hh
namespace HHFK\Route;

use HHFK\Exception\HHFKException;
use HHFK\Controller\Controller;

class Router{
    public static function provide(string $pattern, string $controller): Route{
        $route = new Route($pattern, $controller);
        if (!isset(self::$_routes)){
            self::$_routes = new Vector<Route>();
        }
        self::$_routes[] = $route;
        return $route;
    }

    public static function provided(): Vector<Route>{
        return self::$_routes;
    }

    public static function resolve(): Route{

        
    }

    
    private static Vector<Route> $_routes;
}