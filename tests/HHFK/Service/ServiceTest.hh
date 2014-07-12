<?hh
use HHFK\Service\Service;
use HHFK\Config;

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
    private function _getWaitingContainer()
    {
        $reflect = new ReflectionClass(Service::class);
        $property = $reflect->getProperty('_waiting');
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
        $services = $this->_getServiceContainer()->getValue()->toArray();
        $this->assertArrayHasKey(self::TEST_SERVICE_NAME, $services);
        $this->assertEquals(get_class($services[self::TEST_SERVICE_NAME]), self::TEST_SERVICE_CLASS);
    }

    public function testRegisterServiceAsArgument()
    {}
    public function testRegisterUnknownServiceAsArgument()
    {}

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

    private function prepareServiceAssert()
    {
        $waiting = $this->_getWaitingContainer()->getValue()->toArray();
        $testService = null;
        foreach ($waiting as $pair) {
            if ($pair[0] === self::TEST_SERVICE_NAME) {
                $testService =$pair;
                break;
            }
        }
        $this->assertNotEquals($testService, null);
        $this->assertEquals(self::TEST_SERVICE_NAME, $testService[0]);
        $this->assertEquals($testService[1]['class'], self::TEST_SERVICE_CLASS);
        $this->assertArrayHasKey('to_foo', $testService[1]['arguments']);
        $this->assertEquals($testService[1]['arguments']['to_foo'], 'foo');
    }
    public function testPrepareRegisterService()
    {
        $configuration = array(
            'services' => array(
                self::TEST_SERVICE_NAME => array(
                    'class' => self::TEST_SERVICE_CLASS,
                    'arguments' => self::$TEST_SERVICE_ARGS
                )
            )
        );
        Service::prepare($configuration);
        $this->prepareServiceAssert();
    }

    public function testPrepareReplaceLocalVariable()
    {
        $configuration = array(
            'parameters' => array(
                'test.class' => self::TEST_SERVICE_CLASS
            ),
            'services' => array(
                self::TEST_SERVICE_NAME => array(
                    'class' => "{test.class}",
                    'arguments' => self::$TEST_SERVICE_ARGS
                )
            )
        );
        Service::prepare($configuration);
        $this->prepareServiceAssert();
    }

    public function testPrepareReplaceGlobalVariable()
    {
        Config::set('test.class', self::TEST_SERVICE_CLASS);
        $configuration = array(
            'services' => array(
                self::TEST_SERVICE_NAME => array(
                    'class' => "{{test.class}}",
                    'arguments' => self::$TEST_SERVICE_ARGS
                )
            )
        );
        Service::prepare($configuration);
        $this->prepareServiceAssert();
    }

    public function testBootService()
    {}
}
