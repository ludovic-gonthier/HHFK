<?hh //strict
require_once "../vendor/autoload.php";

use HHFK\Service\Service;
use HHFK\Http\Request;
use HHFK\Kernel;

// Kernel/Or W-e class to load configuration for specified environment
$kernel = new Kernel();

Service::get("router")->resolve(Request::fromCurrentUrl())->send();