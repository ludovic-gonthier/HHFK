<?hh

require_once "../vendor/autoload.php";

use HHFK\Kernel;

function __print():string {
	return "<html><h1>Welcome to HHFK</h1>" . Kernel::TEST . "</html>";
}

echo __print();