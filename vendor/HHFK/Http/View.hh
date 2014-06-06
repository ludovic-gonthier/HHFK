<?hh
namespace HHFK\Http;

class View
{
	const FILE_EXTENSION = ".html";

	public function build($file, $data)
	{
		extract($data);
		ob_start();
		include($file . self::FILE_EXTENSION);
		$tampon = ob_get_contents();
        ob_end_clean();
        $this->_html = $tampon;
	}
	public function display()
	{
		echo $this->_html;
	}

	private string $_html;
}