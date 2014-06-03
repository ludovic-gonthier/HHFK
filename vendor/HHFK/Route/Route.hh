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

	public function __construct(
		private string $_pattern,
		private string $_controller)
	{
		// If the controller is not a valid class
		if (!class_exists($this->_controller)){
			throw new HHFKException($_controller . ": Is not a valid class");
		}
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
	public function setController(string $controller): this
	{
		$this->_controller = $controller;
		return $this;
	}
	public function getController(): string
	{
		return $this->_controller;
	}

	private string $_name;
	private string $_requestType = self::GET;
}