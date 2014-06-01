<?hh
namespace HHFK;

class Kernel
{
	const TEST = "CECI EST UN TEST";

	public function __construct(string $path){
		require_once $path . "/conf/routes.hh";
	}
}