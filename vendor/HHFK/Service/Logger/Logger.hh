<?hh //strict
namespace HHFK\Service\Logger;

use Monolog\Handler\StreamHandler;

class Logger
{
	public function __construct(string $log_path)
	{
		$this->_logger = new \Monolog\Logger("application");
		$this->_logger->pushHandler(new StreamHandler($log_path, \Monolog\Logger::INFO));

		$this->inform("Logger service correctly loaded.");
	}

	public function inform(string $msg, array $datas = array())
	{
		$this->_logger->addInfo($msg, $datas);
	}
	public function notice(string $msg, array $datas = array())
	{
		$this->_logger->addNotice($msg, $datas);
	}
	public function warn(string $msg, array $datas = array())
	{
		$this->_logger->addWarning($msg, $datas);
	}
	public function debug(string $msg, array $datas = array())
	{
		$this->_logger->addDebug($msg, $datas);
	}
	public function error(string $msg, array $datas = array())
	{
		$this->_logger->addError($msg, $datas);
	}


	private \Monolog\Logger $_logger;
}