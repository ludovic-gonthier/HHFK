<?hh
namespace HHFK;

use HHFK\Route\Router;
use HHFK\Route\Url;
use HHFK\Controller\FrontController;

class Kernel
{
	public function __construct(string $path)
	{
		require_once $path . "/conf/routes.hh";

		$url = new Url();
		echo "current URL : '".$url."'<br>";
		foreach (Router::provided() as $route)
			echo "<p>ROUTE '" . $route->getName() . "':  " . $route->getRequestType() . "@" . $route->getPattern() . " --> " . $route->getController() . "</p>";

		$frontController = new FrontController();
		$frontController->dispatch();
	}
}