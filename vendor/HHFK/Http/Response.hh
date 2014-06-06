<?hh
namespace HHFK\Http;

class Response
{
	public function __construct()
	{
		header("HTTP/1.1 200 OK");
	}
	public function send()
	{
		$this->$_view->display();
	}
	public function render(string $template, string $module = null): this
	{
		$this->_view = new View();
		if (isset($module)){
			$module = new $module();
			$template = "";
		}
		$this->_view->build();
		return $this;
	}

	protected View $_view;
}