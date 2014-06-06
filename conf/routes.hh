<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

Router::provide("/user{user_id}/profile", "Test\TestModule\Controller\TestController")
	  ->setName("profil")
	  ->addData("test", "Ta mère plumette")
	  ->setRequestType(Route::GET);