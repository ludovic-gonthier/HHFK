<?hh //strict
namespace HHFK;

/**
 * Class to encapsulate $_SERVER in HHVM
 */
class Server<T> extends Config
{
    protected static Map<string, T> $_configuration = Map{};
}