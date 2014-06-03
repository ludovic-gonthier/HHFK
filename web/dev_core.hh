<?hh

require_once "../vendor/autoload.php";

use HHFK\Kernel;
use HHFK\Controller\Controller;

##TODO put core.hh at the root of project and then pass dir to Kernel

function __print():string {
	$c = new Controller();

	$k = new Kernel(dirname(__DIR__));
	return $c->index("DEV ENVIRONEMENT");
}

echo __print();