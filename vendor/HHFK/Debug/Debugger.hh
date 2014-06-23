<?hh //strict
namespace HHFK\Debug;

class Debugger
{
	public function dump(mixed $value) : void
	{
		echo "<pre>", var_dump($value); "</pre>";
	}
}