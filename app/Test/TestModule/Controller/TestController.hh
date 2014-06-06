<?hh
namespace Test\TestModule\Controller;

use HHFK\Controller\AController;
use HHFK\Http\Response;

class TestController extends AController
{
	public function index(): Response
	{
		return $this->renderFromModule("Test\HomeModule\HomeModule", "index");
	}
}