<?hh
namespace HHFK\Http;

use HHFK\Module\AModule;

class Response
{
	public function __construct()
	{
		$this->_view = new View();
		header("HTTP/1.1 200 OK");
	}
	/**
	 * Send the response
	 * -> Setting the correct HTTP header
	 * -> Displaying the template
	 */
	public function send(): void
	{
		$this->_view->display();
	}
	/**
	 * Render the template file of the response
	 * 
	 * @param  string  $template
	 * @param  AModule $module
	 * @param  array   $data
	 * 
	 * @return Response
	 */
	public function render(string $template, AModule $module, array $data = array()): this
	{
		$directory = $module->getPath() . DIRECTORY_SEPARATOR;
		
		$file = $directory . AModule::DEFAULT_VIEW_FOLDER . DIRECTORY_SEPARATOR . $template;
		$this->_view->build($file, $data);
		return $this;
	}

	protected View $_view;
}