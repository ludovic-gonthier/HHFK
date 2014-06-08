<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

$router = Router::getInstance();

$router->provide("/home", "Test\HomeModule\Controller\TestController")
	   ->setName("home")
	   ->addData("test", "Ta mère plumette")
	   ->setRequestType(Route::GET);