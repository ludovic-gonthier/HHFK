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

		echo "<pre>", var_dump($this->_provider->get("router")->provided()), "</pre>";
	}
	/**
	 * Load the configuration of the application
	 */
	protected function configure():void
	{
		\date_default_timezone_set("Europe/Paris");
		##TODO ParseIniFile for service configuration
		require_once "../conf/services.hh";

		// Importing routes configuration
		$routes = $this->_provider->get("parser")->parseFile("../conf/routes.ini");
		$this->_provider->get("router")->prepare($routes);
	}

	/**
	 * Initialise the modules and the service provider of the application
	 */
	protected function init():void
	{
		$this->_provider = ServiceProvider::getInstance();
		// Providing the router as a service
		$this->_provider->register(new Service("router", "HHFK\Route\Router"));
		// Provide the INI file parser as a service
		$this->_provider->register(new Service("parser", "HHFK\Parser\IniFileParser"));

		self::$_modules = Vector<AModule>{
			new \Test\TestModule\TestModule,
			new \Test\HomeModule\HomeModule
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