<?hh
namespace HHFK\Service;

class Service
{
	public function __construct(
		protected string $_name, 
		protected string $_class,
		protected array $_parameters = null)
	{
	}

	public function get(): mixed
	{
		// Instanciate only when service required
		if (!isset($this->_instance)) {
			$reflect = new \Reflectionclass($this->_class);
			$this->_instance = $reflect->newInstanceArgs($this->_parameters);
		}
		return $this->_instance;
	}
	public function getName(): string
	{
		return $this->_name;
	}

	protected mixed $_instance; // Instance of the $class Class
}