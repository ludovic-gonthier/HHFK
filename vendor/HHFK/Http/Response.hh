<?hh
namespace HHFK\Http;

use HHFK\Module\AModule;

class Response
{
	public function __construct()
	{
		header("HTTP/1.1 200 OK");
	}
	public function send(): void
	{
		$this->_view->display();
	}
	public function render(string $template, AModule $module, mixed $data = array()): this
	{
		$this->_view = new View();
		$directory = $module->getPath() . DIRECTORY_SEPARATOR;
		
		$file = $directory . AModule::DEFAULT_VIEW_FOLDER . DIRECTORY_SEPARATOR . $template;
		$this->_view->build($file, $data);
		return $this;
	}

	protected View $_view;
}