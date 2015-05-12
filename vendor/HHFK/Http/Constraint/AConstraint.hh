<?hh //strict
namespace HHFK\Http\Constraint;

abstract class Constraint<T>
{
    public function __construct(T $expect)
    {
        $this->_expect = $expect;
    }
    public function toRespect((T $value) :bool) $callback) : bool
    {
        return $callback();
    }

    protected T $_expect;
}