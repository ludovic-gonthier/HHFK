<?hh
namespace HHFK;

use HHFK\Service;

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