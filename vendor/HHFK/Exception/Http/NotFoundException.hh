<?hh //strict
namespace HHFK\Exception\Http;

use HHFK\Exception\HHFKException;

class NotFoundException extends HHFKException
{
	public function __construct(string $message = "", int $code = 0, ?\Exception $previous = null)
	{
		parent::__construct($message, $code, $previous);
		header("HTTP/1.1 404 Not Found");
	}	
}