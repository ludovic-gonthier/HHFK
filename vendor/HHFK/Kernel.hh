<?hh //strict

namespace HHFK;

use HHFK\Module\AModule;
use HHFK\Service\ServiceProvider;
use HHFK\Service\Service;

class Kernel
{
	## TODO : instantiate with the environment variable
	public function __construct()
	{
		$this->init();
		$this->configure();
		$this->boot();
	}
	/**
	 * Load the configuration of the application
	 */
	protected function configure():void
	{
		## TODO load the correct loacle from the configuration file
		\date_default_timezone_set("Europe/Paris");
		$parser = $this->_provider->get("parser");
		$services = $parser->parseFile("../conf/services.ini");
		$this->_provider->prepare($services);
		
		// Importing routes configuration
		$routes = $parser->parseFile("../conf/routes.ini");
		$this->_provider->get("router")->prepare($routes);
	}

	/**
	 * Initialise the modules and the service provider of the application
	 */
	protected function init():void
	{
		$this->_provider = ServiceProvider::getInstance();
		// Providing the router as a service
		$this->_provider->register("router", "HHFK\Route\Router");
		// Provide the INI file parser as a service
		$this->_provider->register("parser", "HHFK\Parser\IniFileParser");

		self::$_modules = Vector<AModule>{
			new \Test\TestModule\TestModule(),
			new \Test\HomeModule\HomeModule()
		};
	}

	/**
	 * Boot the module registered in the Kernel
	 * 
	 */
	protected function boot(): void
	{
		foreach (self::$_modules as $module) {
			$module->boot($this->_provider);
		}
		$this->_provider->boot();
	}


	public function provider(): ServiceProvider
	{
		return $this->_provider;
	}
	/**
	 * Fetch a loaded module
	 * 
	 * @param  string $moduleName
	 * 
	 * @return AModule|null The wanted module or null if not present
	 */
	public static function getModule(string $moduleName): ?AModule
	{
		foreach (self::$_modules as $module) {
			if ($module->getName() === $moduleName){
				return $module;
			}
		}
		return null;
	}
	/**
	 * Fetch all the loaded module
	 * 
	 * @return Vector<AModule> Loaded modules
	 */
	public static function getModules(): Vector<AModule>
	{
		return self::$_modules;
	}

	protected ServiceProvider $_provider;
	protected static Vector<AModule> $_modules;
}