<?hh //strict
namespace Test\TestModule\Service;

class Test
{
    public function __construct(string $to_foo)
    {
        $this->_foo = $to_foo;
    }
    public function foo()
    {
        return $this->_foo;
    }
    private string $_foo;
}