<?hh //strict
namespace HHFK\Route;

use HHFK\Controller\Controller;

use HHFK\Exception\HHFKException;
use HHFK\Exception\Oop\ClassNotFoundException;
use HHFK\Exception\Oop\MethodNotFoundException;

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
		$this->_datas = new Map();
		$this->_name = "";
		$this->_requestType = self::GET;
		$this->_action = self::DEFAULT_ACTION;
		$this->checkIsValidController();
	}

	/**
	 * Return the pattern of the route
	 * @return string
	 */
	public function getPattern() : string
	{
		return $this->_pattern;
	}

	/**
	 * Set the request type accepted for this route
	 * @param string $requestType
	 * @return Route Current instance
	 */
	public function setRequestType(string $requestType) : this
	{
		$this->_requestType = $requestType;
		return $this;
	}

	/**
	 * Return the request type accepted for this route
	 * @return string
	 */
	public function getRequestType() : string
	{
		return $this->_requestType;
	}

	/**
	 * Set the name of the route
	 * @param string $name
	 * @return Route Current instance
	 */
	public function setName(string $name) : this
	{
		$this->_name = $name;
		return $this;
	}
	/**
	 * return the name of the route
	 * @return string
	 */
	public function getName() : string
	{
		return $this->_name;
	}
	/**
	 * Check weither the Controller is a valid controller or not
	 * @throws HHFKException If the controller is not valid
	 */
	protected function checkIsValidController() :void
	{
		if (!class_exists($this->_controller)) {
			throw new ClassNotFoundException($this->_controller . ": Class not found.");
		}
	}
	/**
	 * Set the controller for the route and check if it
	 * is a valid one
	 * 
	 * @param string $controller
	 * @return Route Current Instance
	 */
	public function setController(string $controller) : this
	{
		$this->_controller = $controller;
		$this->checkIsValidController();
		return $this;
	}
	/**
	 * Return the controller attached to the route
	 * @return string
	 */
	public function getController() : string
	{
		return $this->_controller;
	}
	/**
	 * Set the action to call in the controller
	 * 
	 * @param string $action
	 * @throws HHFKException If the action doesn't exists in the controller
	 * @return Route Current Instance
	 */
	public function setAction(string $action) : this
	{
		if (!method_exists($this->_controller, $action)) {
			throw new MethodNotFoundException($this->_controller . "::" . $action . "() : Not a method of the class.");
		}
		$this->_action = $action;
		return $this;
	}
	/**
	 * Return the action to call on the route
	 * @return string
	 */
	public function getAction() : string
	{
		return $this->_action;
	}
	/**
	 * Add a data to pass to the controller's action
	 * 
	 * @param string $key
	 * @param mixed  $value
	 * @return Route Current Instance
	 */
	public function addData(string $key, mixed $value) : this
	{
		$this->_datas->add(Pair{$key, $value});
		return $this;
	}
	/**
	 * Remove a data attached to the route
	 * 
	 * @param  string] $key
	 * @return Route Current Instance
	 */
	public function removeData(string $key) : this
	{
		$this->_datas->remove($key);
		return $this;
	}
	/**
	 * Fetch a data with the given key
	 * @param  string $key
	 * @return mixed value of the data or null
	 */
	public function getData(string $key) : ?mixed
	{
		if ($this->_datas->contains($key)){
			return $this->_datas->get($key);
		}
		return null;
	}
	/**
	 * Return all the datas attached to the route
	 * @return ImmMap<string, mixed>
	 */
	public function getDatas() : ImmMap<string, mixed>
	{
		return $this->_datas->toImmMap();
	}

	private string $_name;
	private string $_requestType;
	private string $_action;
	private Map<string, mixed> $_datas;
}