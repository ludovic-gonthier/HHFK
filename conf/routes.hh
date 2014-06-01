<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

Router::provide("/")
	  ->setName("test")
	  ->setRequestParam(Route::POST);

Router::provide("/profile")
	  ->setName("profil")
	  ->setRequestParam(Route::GET);

foreach (Router::provided() as $route)
	echo "<p>ROUTE '" . $route->getName() . "':  " . $route->getRequestType() . "@" . $route->getPattern() . "</p>";