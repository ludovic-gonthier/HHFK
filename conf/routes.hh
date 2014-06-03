<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

Router::provide("/", "HHFK\Controller\Controller")
	  ->setName("test")
	  ->setRequestType(Route::POST)
	  ->setController("");

// Router::provide("/profile", "HHFK\Controller\Controller")
Router::provide("/profile", "Test\TestModule\Controller\TestController")
	  ->setName("profil")
	  ->setRequestType(Route::GET);