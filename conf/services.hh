<?hh //strict

use HHFK\Service\ServiceProvider;
use HHFK\Service\Service;

$provider = ServiceProvider::getInstance();

$provider->register("test.test_service", "Test\TestModule\Service\Test", array("to_foo" => "foo"));


// $services = array(
// 	"test.test_service" => array(
// 		"class" => "Test\TestModule\Service\Test",
// 		"arguments" => array(
// 			"to_foo" => "foo"
// 		)
// 	),
// 	"router" => array(
// 		"class" => "HHFK\Route\Router"
// 	)
// );

// return array("services" => $services);