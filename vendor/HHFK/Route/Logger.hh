<?hh //strict
namespace HHFK\Service\Logger;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;

class Logger
{
	public function __construct(
		private Logger $_logger,
		private StreamHandler $_handler)
	{
	}
}