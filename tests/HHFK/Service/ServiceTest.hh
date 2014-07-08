<?hh
use HHFK\Service\Service;

class ServiceTest extends PHPUnit_Framework_TestCase
{
    const string TEST_SERVICE_NAME = 'test.service',
                 TEST_SERVICE_CLASS = 'Test\TestModule\Service\Test';
    private static $TEST_SERVICE_ARGS = array('to_foo' => 'foo');

    private function _getServiceContainer()
    {
        $reflect = new ReflectionClass(Service::class);
        $property = $reflect->getProperty('_services');
        $property->setAccessible(true);
        return $property;
    }

    private function _insertTestService()
    {
        $property = $this->_getServiceContainer();
        $value = new Map();
        $value[self::TEST_SERVICE_NAME] = (new \ReflectionClass(self::TEST_SERVICE_CLASS))->newInstanceArgs(self::$TEST_SERVICE_ARGS);
        $property->setValue($value);
    }

    public function testServiceExistsFound()
    {
        $this->_insertTestService();
        $this->assertTrue(Service::exists(self::TEST_SERVICE_NAME));
    }
    public function testServiceExistsNotFound()
    {
        $this->assertFalse(Service::exists('test.service.not.found'));
    }

    public function testGetServiceFound()
    {
        $this->_insertTestService();
        $service = Service::get(self::TEST_SERVICE_NAME);
        $this->assertEquals(get_class($service), self::TEST_SERVICE_CLASS);
    }

    public function testServiceInstanciatedOnce()
    {}

    public function testGetServiceNotFound()
    {
        $this->setExpectedException('HHFK\Exception\NotRegisteredException');
        Service::get('unregistered.service');
    }

    public function testRegisterServiceSuccess()
    {
        Service::register(self::TEST_SERVICE_NAME, self::TEST_SERVICE_CLASS, self::$TEST_SERVICE_ARGS);
        $this->assertArrayHasKey(self::TEST_SERVICE_NAME, $this->_getServiceContainer()->getValue()->toArray());
    }

    public function testRegisterServiceUnknownClass()
    {
        $this->setExpectedException('HHFK\Exception\Oop\ClassNotFoundException');
        Service::register(self::TEST_SERVICE_NAME, 'Test\TestModule\Service\UnknownTest');
    }

    public function testRegisterServiceWrongParameters()
    {
        $this->setExpectedException('HHFK\Exception\HHFKException');
        Service::register(self::TEST_SERVICE_NAME, self::TEST_SERVICE_CLASS);
    }

    public function testPrepareRegisterService()
    {}

    public function testPrepareReplaceLocalVariable()
    {}

    public function testPrepareReplaceGlobalVariable()
    {}
}
