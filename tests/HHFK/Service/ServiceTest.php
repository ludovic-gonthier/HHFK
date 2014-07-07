<?php
use HHFK\Service\Service;

class ServiceTest extends PHPUnit_Framework_TestCase
{
    public function testServiceExistsFound()
    {
        Service::register('test.service', 'Test\TestModule\Service\Test', array('foo' => 'foo'));
        $this->assertTrue(Service::exists('test.service'));
    }
    public function testServiceExistsNotFound()
    {
        $this->assertFalse(Service::exists('test.service.not.found'));
    }

    public function testGetServiceFound()
    {}

    public function testServiceInstanciatedOnce()
    {}

    public function testGetServiceNotFound()
    {
        $this->setExpectedException('HHFK\Exception\NotRegisteredException');
        Service::get('unregistered.service');
    }

    public function testRegisterServiceSuccess()
    {
        Service::register('test.service', 'Test\TestModule\Service\Test', array('foo' => 'foo'));
        $service = Service::get('test.service');
        $this->assertEquals(get_class($service), 'Test\TestModule\Service\Test');
    }

    public function testRegisterServiceUnknownClass()
    {
        $this->setExpectedException('HHFK\Exception\Oop\ClassNotFoundException');
        Service::register('test.service', 'Test\TestModule\Service\UnknownTest');
    }

    public function testRegisterServiceWrongParameters()
    {
        Service::register('test.service', 'Test\TestModule\Service\Test');
    }

    public function testPrepareRegisterService()
    {}

    public function testPrepareReplaceLocalVariable()
    {}

    public function testPrepareReplaceGlobalVariable()
    {}
}
