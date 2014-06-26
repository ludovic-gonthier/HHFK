<?hh //partial
namespace HHFK;

/**
 * Class to encapsulate $_SERVER in HHVM
 */
##TODO Serialize session
class Server<T>
{
	/**
	 * Set a variable session
	 *
	 * @param $key string The key to fetch
	 * @return  T|null Return the value corresponding to the key or null if not found
	 */
	public static function get(mixed $key) : ?T
	{
		if (array_ket_exists($key, self::$_server)) {
			return self::$_server[$key];
		}
		return null;
	}
	/**
	 * Set a session variable
	 * 
	 * @param mixed $key   The key in which to store the variable
	 * @param mixed $value The value to store in the Session
	 */
	public static function set(mixed $key, mixed $value) : void
	{
		self::$_server[$key] = $value;
	}

	private array $_server = $_SERVER;
}