<?hh
namespace HHFK;

use HHFK\Module\AModule;

class Kernel
{
	## TODO : instantiate with the environment variable
	public function __construct()
	{
		$this->configure();
		$this->init();
	}

	protected function configure():void
	{
		// Importing routes configuration
		require_once "../conf/routes.hh";

	}

	##TODO use this function in the Controller, instead of recreating an instance
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
		var_dump("Searching for module '" . $moduleName . "'");
		foreach (self::$_modules as $module) {
			var_dump("Name :" . $module->getName());
			if ($module->getName() === $moduleName){
				return $module;
			}
		}
		return null;
	}


	protected static Vector<AModule> $_modules;
}