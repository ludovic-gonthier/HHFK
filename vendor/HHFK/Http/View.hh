<?hh
namespace HHFK\Http;

class View
{
	const FILE_EXTENSION = ".hh"

	public function build($modulePath, $viewFilename)
	{
		extract($data);
		ob_start();
		include($file . self::FILE_EXTENSION);
		$tampon = ob_get_contents();
        ob_end_clean();
		return ($tampon);
	}
	public function display()
	{
		echo $_html;
	}

	private string $_html;
}