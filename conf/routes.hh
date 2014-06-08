<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

$router = Router::getInstance();


$router->provide("/", "Test\TestModule\Controller\TestController");
