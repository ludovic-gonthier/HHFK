<?hh //strict
namespace Test\HomeModule\Controller;

use HHFK\Controller\AController;
use HHFK\Http\Response;

class TestController extends AController
{
    public function index() : Response
    {
        return $this->render("index");
    }
}