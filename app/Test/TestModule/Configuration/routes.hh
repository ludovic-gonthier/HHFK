<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

$router = Router::getInstance();

$router->provide("/test", "Test\TestModule\Controller\TestController")
	   ->setName("test")
	   ->addData("test", "Ta mère plumette")
	   ->setRequestType(Route::GET);


$router->provide("/user/{user_id}/profile", "Test\TestModule\Controller\TestController")
	   ->setName("profil")
	   ->addData("test", "Ta mère plumette")
	   ->setRequestType(Route::GET);