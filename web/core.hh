<?hh
require_once "../vendor/autoload.php";

date_default_timezone_set("Europe/Paris");

use HHFK\Route\Router;
use HHFK\Route\Url;
use HHFK\Kernel;

// Kernel/Or W-e class to load configuration for specified environment
$kernel = new Kernel();

Router::getInstance()->resolve(new Url())->send();