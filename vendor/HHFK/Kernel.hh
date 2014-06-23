<?hh //strict

namespace HHFK;

use HHFK\Module\AModule;
use HHFK\Service\Service;

class Kernel
{
	const string CONF_PATH = "../conf/";
	const string CONF_SERVICES_FILE = "services.ini",
				 CONF_ROUTES_FILE = "routes.ini",
				 CONF_APPLICATION_FILE = "application.ini"

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
	protected function configure() :void
	{
		## TODO load the correct loacle from the configuration file
		\date_default_timezone_set("Europe/Paris");
		$parser = Service::get("parser");
		//Importing services configuration
		$services = $parser->parseFile(self::CONF_PATH . self::CONF_SERVICES_FILE);
		Service::prepare($services);
		
		// Importing routes configuration
		$routes = $parser->parseFile(self::CONF_PATH . self::CONF_ROUTES_FILE);
		Service::get("router")->prepare($routes);
	}

	/**
	 * Initialise the modules and the service provider of the application
	 */
	protected function init() :void
	{
		// Providing the router as a service
		Service::register("router", "HHFK\Route\Router");
		// Provide the INI file parser as a service
		Service::register("parser", "HHFK\Parser\IniFileParser");

		self::$_modules = Vector<AModule>{
			new \Test\TestModule\TestModule(),
			new \Test\HomeModule\HomeModule()
		};
	}

	/**
	 * Boot the module registered in the Kernel
	 * 
	 */
	protected function boot() : void
	{
		foreach (self::$_modules as $module) {
			$module->boot();
		}
		// Late booting for all the applications Service to be registered in the Service class
		Service::boot();
	}

	/**
	 * Fetch a loaded module
	 * 
	 * @param  string $moduleName
	 * 
	 * @return AModule|null The wanted module or null if not present
	 */
	public static function getModule(string $moduleName) : ?AModule
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
	public static function getModules() : Vector<AModule>
	{
		return self::$_modules;
	}

	protected static Vector<AModule> $_modules;
}