<?hh
namespace HHFK\Controller;

class Controller{
	public function index(string $test){
		return "<html><h1>Welcome to HHFK</h1>" . $test . " <h2>Ceci est un titre</h2></html>";
	}
}