<?hh //strict
namespace Test\HomeModule\Controller;

use HHFK\Controller\AController;
use HHFK\Http\Response;

class UserController extends AController
{
    public function index(int $user_id) : Response
    {
        var_dump($user_id);
        return $this->render("index");
    }
    public function birthdate(int $user_id, string $foo) : Response
    {
        var_dump($user_id, $foo);
        return $this->render("index");
    }
}