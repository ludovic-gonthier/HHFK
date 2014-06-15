<?hh //strict
namespace HHFK;

use HHFK\Module\AModule;
use HHFK\Service\ServiceProvider;
use HHFK\Service\Service;
use HHFK\Parser\IniFileParser;

class Kernel
{
	## TODO : instantiate with the environment variable
	public function __construct()
	{
		$this->configure();
		$this->init();

		ServiceProvider::getInstance()->get("test.test_service");
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
		$parser = new IniFileParser();
		$routes = $parser->parseFile("../conf/routes.ini");
		$provider->get("router")->prepare($routes);
		echo "<pre>", var_dump($provider->get("router")->provided()), "</pre>";
	}

	/**
	 * Initialise the modules and the service provider of the application
	 */
	protected function init():void
	{
		self::$_modules = Vector<AModule>{
			new \Test\TestModule\TestModule,
			new \Test\HomeModule\HomeModule
		};
		// Providing the router as a service
		$provider = ServiceProvider::getInstance();
		$provider->register(new Service("router", "HHFK\Route\Router"));
	}

	public static function loadedModule()
	{
		return self::$_modules;
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


	protected static Vector<AModule> $_modules;
}