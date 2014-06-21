<?hh
namespace HHFK\Module;

use HHFK\Controller\AController;
use HHFK\Parser\IniFileParser;
use HHFK\Service\ServiceProvider;

use HHFK\Exception\BadDirectoryException;

abstract class AModule
{
	const string DEFAULT_CONTROLLER_FOLDER = "Controller",
				 DEFAULT_VIEW_FOLDER = "View",
				 DEFAULT_CONFIGURATION_FOLDER = "Configuration";

	public function __construct()
	{
		$this->_controllers = new Vector();
		$this->_name = "";
		$reflect = new \ReflectionObject($this);
		$this->_namespace = $reflect->getNamespaceName();
		$this->_path = dirname($reflect->getFilename());
		$this->_controllerPath = "";
		$this->_configurationPath = "";
	}

	/**
	 * Boot the module
	 * 
	 * @param  ServiceProvider $provider
	 */
	public function boot(ServiceProvider $provider):void
	{
		$this->_controllerPath = $this->getPath() . DIRECTORY_SEPARATOR . self::DEFAULT_CONTROLLER_FOLDER;
		$this->_configurationPath = $this->getPath() . DIRECTORY_SEPARATOR . self::DEFAULT_CONFIGURATION_FOLDER;

		// echo "<pre>", var_dump($provider->get("router")->provided()), "</pre>";die;
		$this->loadConfigurations($provider);
		$this->registerControllers();
	}

	/**
	 * Load the different configuration of the module
	 * Must be put in the "Configuration" folder of the module
	 * @param  ServiceProvider $provider
	 */
	protected function loadConfigurations(ServiceProvider $provider): void
	{
		// Load the Module's route configuration if any
		$routesConfig = $this->_configurationPath  . DIRECTORY_SEPARATOR . "routes.ini";
		if (file_exists($routesConfig)) {
			$routes = $provider->get("parser")->parseFile($routesConfig);
			$provider->get("router")->prepare($routes);
		}
		$servicesConfig = $this->_configurationPath . DIRECTORY_SEPARATOR . "services.hh";
		if (file_exists($servicesConfig)){
			require_once $servicesConfig;
		}
	}

	/**
	 * Register the controller of a module
	 * @throws BadDirectoryException If the "Controller" directory not present
	 */
	protected function registerControllers(): void
	{
		$files = \scandir($this->_controllerPath);
		if ($files === false){
			throw new BadDirectoryException($this->_controllerPath . ": not a valid directory");
		}
		foreach (array_diff($files, array(".", "..")) as $controller){
			//PSR-4 Naming
			$controller = $this->getNamespace() . "\\" . self::DEFAULT_CONTROLLER_FOLDER . "\\" . basename($controller, ".hh");
			// Class added bu the PSR-4 Module autoloader
			if (class_exists($controller) === false ||
				is_subclass_of($controller, "HHFK\Controller\AController") === false){
				continue;
			}
			$this->_controllers[] = $controller;
		}
	}

	/**
	 * Check that a module has a given controller provided
	 * 
	 * @param  string  $controller The controller class name to be checked
	 * @return boolean
	 */
	public function hasController(string $controller): bool
	{
		return $this->_controllers->linearSearch($controller) !== -1;
	}

	/**
	 * Return the namespace of the module
	 * 
	 * @return string namespace name
	 */
	public function getNamespace(): string
	{
		return $this->_namespace;
	}

	/**
	 * Return the path of the module
	 * @return string Path
	 */
	public function getPath(): string
	{
		return $this->_path;
	}

	/**
	 * Return the name of the Module
	 * 
	 * @return string Name of the module
	 */
	public function getName(): string
	{
		if (!isset($this->_name)) {
			$this->_name = static::class;
		}
		return $this->_name;
	}

	protected string $_path;
	protected string $_namespace;
	protected string $_name;

	private string $_controllerPath;
	private string $_configurationPath;

	protected Vector<string> $_controllers;
}