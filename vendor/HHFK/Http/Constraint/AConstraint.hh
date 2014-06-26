<?hh //strict
namespace HHFK\Http\Constraint;

abstract class AConstraint<T>
{
	public function __construct(T $expected)
	{
		$this->_expect = $expected;
	}
	
	abstract public function respect(T $given) : bool;

	protected T $_expect;
}