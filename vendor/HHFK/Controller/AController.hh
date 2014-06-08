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
		protected Request $_request = null,
		protected Response $_response = null)
	{
		if ($this->_request === null) {
			$this->_request = new Request;
		}
		if ($this->_response === null) {
			$this->_response = new Response;
		}
		foreach (Kernel::getModules() as $module) {
			if ($module->hasController(static::class)){
				$this->_module = $module;
				break;
			}
		}
		if (!isset($this->_module)){
			throw new HHFKException("Your controller is not attach to a module.");
		}
	}

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
		$module = Kernel::getModule($module);
		if ($module === null) {
			throw new HHFKException($module . ": The module as not been load, please see to add him to the Kernel");	
		}
		return $this->_response->render($template, $module);
	}

	public function registerModule(AModule $module): void
	{
		$this->_module = $module;
	}
	public function getModule(): AModule
	{
		return $this->_module;
	}

	protected AModule $_module;
}