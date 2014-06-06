<?hh
require_once "../vendor/autoload.php";

use HHFK\Route\Router;
use HHFK\Route\Url;
use HHFK\Kernel;


		// $module = new Test\TestModule\TestModule();
// Kernel/OrW-e class to load configuration for specified environment
$kernel = new Kernel();

Router::resolve(new Url())->send();