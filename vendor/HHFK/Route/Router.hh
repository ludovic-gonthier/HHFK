<?hh
namespace HHFK\Route;

class Router{
	private static Vector<Route> $_routes;

	public static function provide(string $pattern): Route{
		$route = new Route($pattern);
		if (!isset(self::$_routes)){
			self::$_routes = new Vector<Route>();
		}
		self::$_routes[] = $route;
		return $route;
	}

	public static function provided(): Vector<Route>{
		return self::$_routes;
	}
}