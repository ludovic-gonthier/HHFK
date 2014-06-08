<?hh

use HHFK\ServiceProvider;
use HHFK\Service;

$provider = ServiceProvider::getInstance();

$service = new Service("test.test_service", "HHFK\Test\TestModule\Service\Test.hh");
$provider->register($service);
