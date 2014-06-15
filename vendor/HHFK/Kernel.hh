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

	protected function configure():void
	{
		\date_default_timezone_set("Europe/Paris");

		require_once "../conf/services.hh";

		// Importing routes configuration
		$parser = new IniFileParser();
		$routes = $parser->parseFile("../conf/routes.ini");
		$provider->get("router")->prepare($routes);
		echo "<pre>", var_dump($provider->get("router")->provided()), "</pre>";
	}

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
	public static function getModule(string $moduleName)
	{
		foreach (self::$_modules as $module) {
			if ($module->getName() === $moduleName){
				return $module;
			}
		}
		return null;
	}
	public static function getModules()
	{
		return self::$_modules;
	}


	protected static Vector<AModule> $_modules;
}