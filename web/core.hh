<?hh
require_once "../vendor/autoload.php";

use HHFK\Service\ServiceProvider;
use HHFK\Route\Url;
use HHFK\Kernel;

// Kernel/Or W-e class to load configuration for specified environment
$kernel = new Kernel();

$router = ServiceProvider::getInstance()->get("router");
$router->resolve(new Url())->send();