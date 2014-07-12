<?hh

use HHFK\Config;

class ConfigTest extends PHPUnit_Framework_TestCase
{
    private function _accessConfiguration()
    {
        $reflect = new ReflectionClass(Config::class);
        $property = $reflect->getProperty('_configuration');
        $property->setAccessible(true);
        return $property;
    }
    private function _fillTestConfig()
    {
        $property = $this->_accessConfiguration();
        $value = new Map();
        $value["test_key"] = "test_value";
        $property->setValue($value);
    }

    public function testPopulate()
    {
        $config = array(
            "test_key" => "test_value"
        );
        Config::populate($config);
        $property = $this->_accessConfiguration();

    }
    /*
    public function testAll()
    {}

    public function testExistsFound()
    {}
    public function testExistsNotFound()
    {}

    public function testGetFound()
    {

    }
    public function testGetNotFound()
    {}

    public function testSet()
    {}
    public function testRemove()
    {}
    */
}