<?hh //partial

namespace HHFK;

use HHFK\Server;

use HHFK\Module\AModule;
use HHFK\Service\Service;

use HHFK\Exception\HHFKException;

class Kernel
{
	const string CONF_PATH = "../conf/";
	const string CONF_SERVICES_FILE = "services.ini",
				 CONF_ROUTES_FILE = "routes.ini",
				 CONF_APPLICATION_FILE = "application.ini";

	## TODO : instantiate with the environment variable
	public function __construct()
	{
		self::$_modules = new Vector();
		self::$_modules->add(new \Test\TestModule\TestModule());
		self::$_modules->add(new \Test\HomeModule\HomeModule());

		$this->init();
		$this->configure();
		$this->boot();

		Service::get("debugger")->dump(Server::all());
	}
	/**
	 * Load the configuration of the application
	 */
	protected function configure() : void
	{
		if (Config::exists("timezone") === false) {
			\date_default_timezone_set(\date_default_timezone_get());
			Service::get("logger")->warn("No timezone setted from configuration file. Default timezone setted.");
		} else {
			$tz = Config::get("timezone");
			if (\date_default_timezone_set($tz) === false) {
				## TODO Correct exception
				throw new HHFKException("Timezone identifier '" . $tz . "' is not a valid one.");
			}
			if (Config::get("debug") === true) {
				Service::get("logger")->inform("Default timezone setted to: '" . $tz . "'");
			}
		}

	}

	/**
	 * Initialise the modules and the service provider of the application
	 */
	protected function init() :void
	{
		// Provide the INI file parser as a service
		Service::register("parser", "HHFK\Parser\IniFileParser");

		$parser = Service::get("parser");
		//Importing services configuration
		$services = $parser->parseFile(self::CONF_PATH . self::CONF_SERVICES_FILE);
		Service::prepare($services);

		// Importing application environment configuration
		$configuration = $parser->parseFile(self::CONF_PATH . self::CONF_APPLICATION_FILE);
		Config::populate($configuration);

		// In debug mode, add the debugger as a service
		if (Config::get("debug") == true) {
			Service::register("debugger", "HHFK\Debug\Debugger");
		}

		// Providing the router as a service
		Service::register("router", "HHFK\Route\Router");
		// Importing routes configuration
		$routes = $parser->parseFile(self::CONF_PATH . self::CONF_ROUTES_FILE);
		Service::get("router")->prepare($routes);
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