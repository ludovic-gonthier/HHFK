<?hh //strict
namespace HHFK;

/**
 * Class to encapsulate $_SERVER in HHVM
 */
class Server<T> extends Config<T>
{
    ##TODO for the most default value, create an associated function
    // requestUri(), requestType(), host(), etc.
    protected static Map<string, T> $_configuration = Map{};
}