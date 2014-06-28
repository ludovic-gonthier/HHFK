<?hh //strict
namespace HHFK\Http;

use HHFK\Route\Route;
use HHFK\Route\Url;

class Request
{    
    const string     GET = "GET",
                      POST = "POST",
                      UPDATE = "UPDATE",
                      DELETE = "DELETE",
                      PUT = "PUT",
                      ALL = "ALL";

    public function __construct(Url $url)
    {
        $this->_url = $url;
        $this->_route = null;
    }

    /**
     * Bind a Route to the request
     * 
     * @param  Route    $route The route to bind to the Request
     */
    public function bindRoute(Route $route) : void
    {
        $this->_route = $route;
    }
    /**
     * Bind a URL to the request
     * 
     * @param  Url    $url The URL to bind to the Request
     */
    public function bindUrl(Url $url) : void
    {
        $this->_url = $url;
    }

    public function getBindedRoute() : ?Route
    {
        return $this->_route;
    }
    /**
     * Return the URL binded to the request
     * 
     * @return Url The url binded to the request
     */
    public function getBindedUrl() : Url
    {
        return $this->_url;
    }

    public function parameter(string $key, string $request = self::ALL) : void
    {
        ## TODO
    }

    /**
     * Construct a Request from teh current URL
     * 
     * @return Request Created Request
     */
    public static function fromCurrentUrl() : this
    {
        return new static(new Url());
    }

    protected ?Route $_route;
    protected Url $_url;
}