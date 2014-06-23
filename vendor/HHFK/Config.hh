<?hh //strict

namespace HHFK;

class Config<T>
{
	/**
	 * Private constructor becasue the class is static
	 */
	private function __construct()
	{}

	public static function populate(array $config) : void
	{
		foreach ($config as $key => $value) {
			self::$_configuration[$key] = $value;
		}
	}

	public static function all() : ImmMap<string, T>
	{
		return self::$_configuration->toImmMap();
	}

	public static function exists(string $key) : bool
	{
		return self::$_configuration->contains($key);
	}

	public static function get(string $key): ?T
	{
		if (self::$_configuration->contains($key)) {
			return self::$_configuration->get($key);
		}
		return null;
	}
	public static function set(string $key, T $value) : void
	{
		self::$_configuration[$key] = $value;
	}

	private static Map<string, T> $_configuration = Map{};
}