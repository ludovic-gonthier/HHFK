<?hh
namespace HHFK\Route;

use HHFK\Controller\Controller;
use HHFK\Exception\HHFKException;

class Route
{
	const string 	GET = "GET",
		  			POST = "POST",
		  			UPDATE = "UPDATE",
		  			DELETE = "DELETE",
		  			PUT = "PUT";

	const string 	DEFAULT_ACTION = "index";

	public function __construct(
		private string $_pattern,
		private string $_controller)
	{
		// If the controller is not a valid class
		$this->checkIsValidController();
		$this->_datas = new Map<string, mixed>;
	}

	public function getPattern(): string
	{
		return $this->_pattern;
	}

	public function setRequestType(string $requestType): this
	{
		$this->_requestType = $requestType;
		return $this;
	}

	public function getRequestType(): string
	{
		return $this->_requestType;
	}

	public function setName(string $name): this
	{
		$this->_name = $name;
		return $this;
	}
	public function getName(): string
	{
		return $this->_name;
	}
	protected function checkIsValidController()
	{
		if (!class_exists($this->_controller)) {
			throw new HHFKException($_controller . ": Is not a valid class");
		}
	}
	public function setController(string $controller): this
	{
		$this->_controller = $controller;
		$this->checkIsValidController();
		return $this;
	}
	public function getController(): string
	{
		return $this->_controller;
	}

	public function setAction(string $action): this
	{
		if (!method_exists($this->_controller, $action)){
			throw new HHFKException($action . ": Is not a method of the class " . $this->_controller);
		}
		$this->_action = $action;
		return $this;
	}
	public function getAction(): string
	{
		return $this->_action;
	}
	public function addData(string $key, mixed $value): this
	{
		$this->_datas->add(Pair{$key, $value});
		return $this;
	}
	public function removeData($key): this
	{
		$this->_datas->remove($key);
		return $this;
	}
	public function getData(string $key): mixed
	{
		if ($this->_datas->contains($key)){
			return $this->_datas->get($key);
		}
	}
	public function getDatas(): ImmMap<string, mixed>
	{
		return $this->_datas->toImmMap();
	}

	private string $_name;
	private string $_requestType = self::GET;
	private string $_action = self::DEFAULT_ACTION;
	private Map<string, mixed> $_datas;
}