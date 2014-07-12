<?hh //strict

namespace HHFK;

class Config<T>
{
    /**
     * Private constructor becasue the class is static
     */
    protected function __construct()
    {}

    public static function populate(array<string, T> $config) : void
    {
        foreach ($config as $key => $value) {
            static::$_configuration[$key] = $value;
        }
    }

    public static function all() : ImmMap<string, T>
    {
        return static::$_configuration->toImmMap();
    }

    public static function exists(string $key) : bool
    {
        return static::$_configuration->contains($key);
    }

    public static function get(string $key): ?T
    {
        if (static::$_configuration->contains($key)) {
            return static::$_configuration->get($key);
        }
        return null;
    }
    public static function set(string $key, T $value) : void
    {
        static::$_configuration[$key] = $value;
    }
    public static function remove(string $key)
    {
        static::$_configuration->remove($key);
    }

    protected static Map<string, T> $_configuration = Map{};
}