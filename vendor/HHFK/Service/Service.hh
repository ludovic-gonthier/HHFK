<?hh
namespace HHFK\Service;

class Service
{
	public function __construct(
		protected string $_name, 
		protected string $_class,
		protected array $_parameters = array())
	{
		$this->_instance = null;
	}

	/**
	 * Fetch a Service
	 * Instantiate it if not already loaded
	 * 
	 * @return mixed The service class
	 */
	public function get(): mixed
	{
		// Instanciate only when service required
		if (!isset($this->_instance)) {
			//Instanciate all the class passed as parameter
			## TODO Take care of recursive inclusion
			foreach ($this->_parameters as $name => $parameter){
				// If a parameter is a registered class
				if (class_exists($parameter) === false) {
					continue;
				}
				
				$provider = ServiceProvider::getInstance();
				if ($provider->serviceExists($parameter)) {// instance of Service
					$this->_parameters[$name] = $provider->get($parameter);
				}
			}
			$reflect = new \Reflectionclass($this->_class);
			$this->_instance = $reflect->newInstanceArgs($this->_parameters);
		}
		return $this->_instance;
	}
	/**
	 * Return the name of the service
	 * @return string
	 */
	public function getName(): string
	{
		return $this->_name;
	}

	protected mixed $_instance; // Instance of the $class Class
}