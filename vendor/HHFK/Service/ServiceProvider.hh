<?hh
namespace HHFK\Service;

use HHFK\Service\Service;
use HHFK\Exception\HHFKException;


##TODO pass service provider to Controller as attributes $_services;
class ServiceProvider
{
	protected function __construct()
	{
		$this->_services = new Map<string, Service>;
	}

	/**
	 * Register a service in the provider
	 * 
	 * @param  Service $service
	 */
	public function register(Service $service):void
	{
		$this->_services[$service->getName()] = $service;
	}
	/**
	 * Return the registered service in the provider
	 * @return ImmMap<string, Service>
	 */
	public function registered():ImmMap<string, Service>
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
	public function get(string $serviceName): mixed
	{
		$service = $this->_services->get($serviceName);
		if ($service === null){
			##TODO Correct Exception tree
			throw new HHFKException("The service '" . $serviceName . "' requested is not registered");
		}
		return $service->get();
	}

	/**
	 * Return an instance of the ServiceProvider
	 * @return ServiceProvider
	 */
	public static function getInstance(): this
	{
		if (!isset(self::$_instance)){
			self::$_instance = new self;
		}
		return self::$_instance;
	}

	protected Map<string, Service> $_services;
	protected static ServiceProvider $_instance = null;
}