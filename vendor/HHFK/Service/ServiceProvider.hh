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

	public function register(Service $service)
	{
		$this->_services[$service->getName()] = $service;
	}
	public function registered()
	{
		return $this->_services;
	}
	public function serviceExists(string $serviceName): bool
	{
		return $this->_services->contains($serviceName);
	}
	public function get(string $serviceName): mixed
	{
		$service = $this->_services->get($serviceName);
		if ($service === null){
			##TODO Correct Exception tree
			throw new HHFKException("The service '" . $serviceName . "' requested is not registered");
		}
		return $service->get();
	}

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