<?hh //strict
namespace Test\TestModule\Service;

class Foo
{
    public function __construct(Bar $bar)
    {
        $this->_bar = $bar;
    }
    public function bar() : Bar
    {
        return $this->_bar;
    }
    private Bar $_bar;
}