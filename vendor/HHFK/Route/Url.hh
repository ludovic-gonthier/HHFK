<?hh //strict
namespace HHFK\Route;

use HHFK\Exception\HHFKException;

class Url{
	const 	URL_SCHEME = "scheme",
			URL_HOST = "host",
			URL_PORT = "port",
			URL_USER = "user",
			URL_PASS = "pass",
			URL_PATH = "path",
			URL_QUERY = "query",
			URL_FRAGMENT = "fragment";

	public function __construct(string $url = "")
	{
		if (empty($url) && array_key_exists('REQUEST_URI', $_SERVER) && array_key_exists('HTTP_HOST', $_SERVER)
		  && array_key_exists('HTTPS', $_SERVER)) {
			$hhtps = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] == 'on') ? "s" : "";
			$url = sprintf("http%s://%s%s", $hhtps, $_SERVER["HTTP_HOST"], $_SERVER["REQUEST_URI"]);
		}

		if (($parsed = \parse_url($url)) === false){
			throw new HHFKException($url . ": Is not a valid URL");
		}
		$this->_scheme   = isset($parsed[self::URL_SCHEME]) ? $parsed[self::URL_SCHEME] : '';
		$this->_host     = isset($parsed[self::URL_HOST]) ? $parsed[self::URL_HOST] : '';
		$this->_port     = isset($parsed[self::URL_PORT]) ? $parsed[self::URL_PORT] : 0;
		$this->_user     = isset($parsed[self::URL_USER]) ? $parsed[self::URL_USER] : '';
		$this->_pass     = isset($parsed[self::URL_PASS]) ? $parsed[self::URL_PASS]  : '';
		$this->_path     = isset($parsed[self::URL_PATH]) ? $parsed[self::URL_PATH] : '';
		$this->_query    = isset($parsed[self::URL_QUERY]) ? $parsed[self::URL_QUERY] : '';
		$this->_fragment = isset($parsed[self::URL_FRAGMENT]) ? $parsed[self::URL_FRAGMENT] : '';
	}
	/**
	 * print the URL
	 * @return string
	 */
	public function __toString(): string
	{
		$pass = ($this->_user || $this->_pass) ? ':' . $this->_pass . "@" : '';
		$port = $this->_port === 0 ? '' : ':' . $this->_port;
		return sprintf("%s%s%s%s%s%s%s%s",
			$this->_scheme . '://', $this->_user, $pass, $this->_host,
			$port, $this->_path, '?' . $this->_query, '#' . $this->_fragment);
	}

	/**
	 * Return the scheme of the URL
	 * @return string
	 */
	public function getScheme(): string
	{
		return $this->_scheme;
	}
	/**
	 * Return the port of the URL
	 * @return int
	 */
	public function getPort(): int
	{
		return $this->_port;
	}
	/**
	 * Return the host of the URL
	 * @return string
	 */
	public function getHost(): string
	{
		return $this->_host;
	}
	/**
	 * Return the user of the URL
	 * @return string
	 */
	public function getUser(): string
	{
		return $this->_user;
	}
	/**
	 * Return the pass of the URL
	 * @return string
	 */
	public function getPass(): string
	{
		return $this->_pass;
	}
	/**
	 * Return the query of the URL
	 * @return string
	 */
	public function getQuery(): string
	{
		return $this->_query;
	}
	/**
	 * Return the path of the URL
	 * @return string
	 */
	public function getPath(): string
	{
		return $this->_path;
	}
	/**
	 * Return the fragment of the URL
	 * @return string
	 */
	public function getFragment(): string
	{
		return $this->_fragment;
	}

	protected int 		$_port;
	protected string 	$_scheme,
						$_host,
						$_user,
						$_pass,
						$_path,
						$_query,
						$_fragment;

}