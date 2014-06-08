<?hh
namespace HHFK;

class Service
{
	public function __construct(
		protected string $_name, 
		protected string $_class,
		protected ImmMap<string, string> $_parameters = null)
	{

	}

	public function get(): mixed
	{
		// Instanciate only when service required
		if (!isset($this->_instance)) {
			$this->_instance = new $this->_class;
		}
	}
	public function getName(): string
	{
		return $this->_name;
	}

	protected mixed $_instance; // Instance of the $class Class
}