<?hh //strict
namespace HHFK\Controller;

use HHFK\Kernel;

use HHFK\Http\Request;
use HHFK\Http\Response;
use HHFK\Http\RedirectResponse;

use HHFK\Route\Url;

use HHFK\Module\AModule;

use HHFK\Service\Service;

use HHFK\Exception\HHFKException;

abstract class AController{
	public function __construct(
		protected ?Request $_request = null)
	{
		if ($this->_request === null) {
			$this->_request = Request::fromCurrentUrl();
		}
		$this->_response = new Response();
		$this->_module = null;
		foreach (Kernel::getModules() as $module) {
			if ($module->hasController(static::class)){
				$this->_module = $module;
				break;
			}
		}
		if (!isset($this->_module)){
			## TODO Correct Exception
			throw new HHFKException("Your controller is not attach to a module.");
		}
	}

	## TODO pass the correct argument
	protected function redirect(): Response
	{
		return new RedirectResponse();
	}

	/**
	 * Render a template in the current module
	 * 
	 * @param  string $template
	 * @return Response
	 */
	protected function render(string $template): Response
	{
		return $this->_response->render($template, $this->getModule());
	}
	/**
	 * [renderFromModule description]
	 * @param  string $module
	 * @param  string $template
	 * @return Response
	 *
	 * @throws HHFKException If the given module is not a valid module
	 * @throws HHFKException If the given module has not been initialized
	 */
	protected function renderFromModule(string $module, string $template): Response
	{
		if (!\class_exists($module)) {
			throw new HHFKException($module . ": Is not a valid Module Class");
		}
		$module = Kernel::getModule($module);
		if ($module === null) {
			throw new HHFKException($module . ": The module as not been load, please see to add him to the Kernel");	
		}
		return $this->_response->render($template, $module);
	}

	/**
	 * Bind a module to the controller
	 * 
	 * @param  AModule $module
	 */
	public function registerModule(AModule $module): void
	{
		$this->_module = $module;
	}
	/**
	 * Return the module that is binded to the Controller
	 * 
	 * @return AModule
	 */
	public function getModule(): AModule
	{
		return $this->_module;
	}

	protected Response $_response;
	protected AModule $_module;
}