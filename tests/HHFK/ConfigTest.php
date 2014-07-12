<?hh

use HHFK\Config;

class ConfigTest extends PHPUnit_Framework_TestCase
{
    const CONFIG_KEY = "test_key";
    const CONFIG_VALUE = "test_value";

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
        $value[self::CONFIG_KEY] = self::CONFIG_VALUE;
        $property->setValue($value);
    }

    public function testPopulate()
    {
        $config = array(
            self::CONFIG_KEY => self::CONFIG_VALUE
        );
        Config::populate($config);
        $values = $this->_accessConfiguration()->getValue()->toArray();
        $this->assertArrayHasKey(self::CONFIG_KEY, $values);
        $this->assertEquals($values[self::CONFIG_KEY], self::CONFIG_VALUE);
    }

    public function testAll()
    {
        $config = Config::all()->toArray();
        $this->assertArrayHasKey(self::CONFIG_KEY, $config);
        $this->assertEquals($config[self::CONFIG_KEY], self::CONFIG_VALUE);
    }

    public function testExistsFound()
    {
        $this->assertTrue(Config::exists(self::CONFIG_KEY));
    }
    public function testExistsNotFound()
    {
        $this->assertFalse(Config::exists('unknown'));
    }

    public function testGetFound()
    {
        $value = Config::get(self::CONFIG_KEY);
        $this->assertEquals($value, self::CONFIG_VALUE);
    }
    public function testGetNotFound()
    {
        $value = Config::get('unknown');
        $this->assertNull($value);
    }

    public function testRemove()
    {
        Config::remove(self::CONFIG_KEY);
        $values = $this->_accessConfiguration()->getValue()->toArray();
        $this->assertCount(0, $values);
    }

    public function testSet()
    {
        Config::set(self::CONFIG_KEY, self::CONFIG_VALUE);
        $values = $this->_accessConfiguration()->getValue()->toArray();
        $this->assertArrayHasKey(self::CONFIG_KEY, $values);
        $this->assertEquals($values[self::CONFIG_KEY], self::CONFIG_VALUE);
    }
}