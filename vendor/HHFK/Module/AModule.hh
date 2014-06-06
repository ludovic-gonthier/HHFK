<?hh
namespace HHFK\Module;

use HHFK\Controller\AController;

use HHFK\Exception\BadDirectoryException;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;

abstract class AModule
{
	const string DEFAULT_CONTROLLER_FOLDER = "Controller",
				 DEFAULT_VIEW_FOLDER = "View",
				 DEFAULT_CONFIGURATION_FOLDER = "Configuration";

	private Logger $_logger;

	public function __construct()
	{
		$this->_controllers = new Vector<AController>();

		$this->_logger = new Logger(static::class);
		$this->_logger->pushHandler(new StreamHandler('/var/log/lgo/info.log', Logger::INFO));

		$this->loadConfigurations();
		$this->registerControllers();
	}

	protected function loadConfigurations(): void
	{

	}

	protected function registerControllers(): void
	{
		$files = \scandir($dirname = $this->getPath() . DIRECTORY_SEPARATOR . self::DEFAULT_CONTROLLER_FOLDER);
		if ($files === false){
			throw new BadDirectoryException($dirname . ": Is not a valid directory");
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
			$this->_logger->addInfo("Attaching '" . static::class . "' to " . $controller );
		}
	}

	public function hasController(string $controller): bool
	{
		return $this->_controllers->linearSearch($controller) !== -1;
	}

	public function getNamespace(): string
	{
		if (!isset($this->_namespace)){
			$reflect = new \ReflectionObject($this);
			$this->_namespace = $reflect->getNamespaceName();
		}
		return $this->_namespace;
	}

	public function getPath(): string
	{
		if (!isset($this->_path)) {
			$reflect = new \ReflectionObject($this);
			$this->_path = dirname($reflect->getFilename());
		}
		return $this->_path;
	}

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

	protected Vector<AController> $_controllers;
}