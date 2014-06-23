<?hh //strict
namespace Test\HomeModule\Controller;

use HHFK\Controller\AController;
use HHFK\Http\Response;

class UserController extends AController
{
	public function index($user_id) : Response
	{
		var_dump($user_id);
		return $this->render("index", array("user_id" => $user_id));
	}
	public function birthdate($user_id, $foo) : Response
	{
		var_dump($user_id, $foo);
		return $this->render("index", array("user_id" => $user_id));
	}
}