<?hh

use HHFK\Service\ServiceProvider;
use HHFK\Service\Service;

$provider = ServiceProvider::getInstance();

$service = new Service("test.test_service", "Test\TestModule\Service\Test", array("to_foo" => "foo"));
$provider->register($service);
