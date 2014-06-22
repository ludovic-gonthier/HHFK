<?hh //strict
require_once "../vendor/autoload.php";

use HHFK\Service\ServiceProvider;
use HHFK\Http\Request;
use HHFK\Kernel;

// Kernel/Or W-e class to load configuration for specified environment
$kernel = new Kernel();

$kernel->provider()->get("router")->resolve(Request::fromCurrentUrl())->send();