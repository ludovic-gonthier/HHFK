<?hh
namespace HHFK;

use HHFK\Module\AModule;
use HHFK\Service\ServiceProvider;

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
		// Importing routes configuration
		require_once "../conf/routes.hh";
		require_once "../conf/services.hh";
	}

	protected function init():void
	{
		self::$_modules = Vector<AModule>{
			new \Test\TestModule\TestModule,
			new \Test\HomeModule\HomeModule
		};
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