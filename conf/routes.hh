<?hh

use HHFK\Route\Route;
use HHFK\Route\Router;

$router = Router::getInstance();


$router->provide("/", "Test\TestModule\Controller\TestController");

/*
[home]
	pattern="/"
	controller="Test\TestModule\Controller\TestController"
	[home:options]
		method="GET|POST"
	[home:datas]
		key="value"
	[home:regexp]
		variable_name="regexp_string"

[user.profil]
	pattern="/user/{user_id}/profile"
*/