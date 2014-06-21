<?hh
namespace HHFK\Service;

use HHFK\Service\Service;
use HHFK\Exception\HHFKException;
use HHFK\Exception\NotRegisteredException;


## TODO pass service provider to Controller as attributes $_services;
class ServiceProvider<T>
{
	protected function __construct()
	{
		$this->_services = new Map();
	}

	/**
	 * Register a service in the provider
	 * 
	 * @param  Service $service
	 */
	public function register(string $name, string $class, array $parameters = array()):void
	{
		foreach ($parameters as $label => $parameter) {
			// If a parameter is a registered class
			if (class_exists($parameter) === false) {
				continue;
			}
			##TODO take care of recursive Servie Registration
			if ($this->serviceExists($parameter)) {// instance of Service
				$parameters[$label] = $this->get($parameter);
			}
		}
		$reflect = new \Reflectionclass($class);
		$this->_services[$name] = $reflect->newInstanceArgs($parameters);
	}
	/**
	 * Return the registered service in the provider
	 * @return ImmMap<string, Service>
	 */
	public function registered():ImmMap<string, T>
	{
		return $this->_services->toImmMap();
	}
	/**
	 * Check if a service exists
	 * 
	 * @param  string $serviceName
	 * @return bool
	 */
	public function serviceExists(string $serviceName): bool
	{
		return $this->_services->contains($serviceName);
	}
	/**
	 * Fetch a registered service
	 * 
	 * @param  string $serviceName
	 * @return mixed Instance of the service
	 * @throws HHFKException If the service is not registered
	 */
	public function get(string $serviceName): T
	{
		$service = $this->_services->get($serviceName);
		if ($service === null) {
			throw new NotRegisteredException("Service '" . $serviceName . "' requested is not registered");
		}
		return $service;
	}

	/**
	 * Return an instance of the ServiceProvider
	 * @return ServiceProvider
	 */
	public static function getInstance(): ?this
	{
		if (!isset(self::$_instance)) {
			self::$_instance = new static();
		}
		return self::$_instance;
	}

	protected Map<string, T> $_services;
	private static ?ServiceProvider $_instance = null;
}