<?hh
namespace HHFK\Route;

type string = string;
// type callback = ;

class Route
{
	const string 	GET = "GET",
		  			POST = "POST",
		  			UPDATE = "UPDATE",
		  			DELETE = "DELETE",
		  			PUT = "PUT";

	private string $_name;
	private string $_requestType = self::GET;

	public function __construct(
		private string $_pattern
		){
		// Add the route to a container
	}

	public function getPattern(): string{
		return $this->_pattern;
	}

	public function setRequestType(string $requestType): this{
		$this->_requestType = $requestType;
		return $this;
	}
	public function getRequestType(): string{
		return $this->_requestType;
	}

	public function setName(string $name): this{
		$this->_name = $name;
		return $this;
	}
	public function getName(): string{
		return $this->_name;
	}
}