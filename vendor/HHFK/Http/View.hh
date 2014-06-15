<?hh
namespace HHFK\Http;

class View
{
	const FILE_EXTENSION = ".html";

	/**
	 * Build the view from a template file
	 * 
	 * @param  string $file
	 * @param  array $data
	 */
	public function build(string $file, array $data): void
	{
		extract($data);
		ob_start();
		include($file . self::FILE_EXTENSION);
		$tampon = ob_get_contents();
        ob_end_clean();
        $this->_html = $tampon;
	}

	/**
	 * Display the view
	 * @return [type]
	 */
	public function display()
	{
		echo $this->_html;
	}

	private string $_html;
}