<?hh
namespace HHFK\Controller;

use HHFK\Kernel;

use HHFK\Http\Request;
use HHFK\Http\Response;
use HHFK\Http\RedirectResponse;

use HHFK\Module\AModule;

use HHFK\Exception\HHFKException;

abstract class AController{
	public function __construct(
		private Request $request = null,
		private Response $response = null)
	{
	}

	abstract public function index(): Response;

	protected function redirect($html): Response
	{
		return new RedirectResponse($html);
	}

	protected function render(string $template): Response
	{
		return $this->_response->render($template, $this->getModule());
	}
	protected function renderFromModule(string $module, string $template): Response
	{
		if (!class_exists($module)) {
			throw new HHFKException($module . ": Is not a valid Module Class");
		}
		if (($module = Kernel::getModule($module)) === null) {
			throw new HHFKException($module . ": The module as not been load, please see to add him to the Kernel");	
		}
		var_dump($module);die;
		return $this->_response->render($template, $module);
	}

	public function registerModule(AModule $module): void
	{
		self::$_module = $module;
	}
	public function getModule(): AModule
	{
		return self::$_module;
	}

	protected static AModule $_module;
}