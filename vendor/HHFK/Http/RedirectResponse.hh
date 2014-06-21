<?hh //strict
namespace HHFK\Http;

class RedirectResponse extends Response
{
	public function __construct()
	{
		parent::__construct();
		header("HTTP/1.1 301 Moved Permanently");
	}
}