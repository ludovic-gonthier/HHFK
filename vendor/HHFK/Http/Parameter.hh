<?hh // strict
namespace HHFK\Http;

use HHFK\Server;

use HHFK\Http\HttpMethod;
use HHFK\Http\Method;

class Parameter<T>
{
    public function __construct(HttpMethod $method)
    {
        $this->_method = $method;
        if ($method === Method::GET) {
            $this->_datas = $_GET;
            unset($_GET);
        } else if ($method === Method::POST) {
            $this->_datas = $_POST;
            unset($_POST);
        } else {
            $datas = \file_get_contents('php://input');
            if ($datas === false) {
                ##TODO correct Exception
                throw new \Exception("Can't read input");
            }
            \parse_str($datas, $this->_datas);
        }
    }

    private function _isCurrentRequest()
    {
        if ($this->_method !== Server::get('REQUEST_METHOD')) {
            ##TODO correct Exception
            throw new \Exception("Can't access '" . $this->_method . "' parameters when on a request of type '" . Server::get('REQUEST_METHOD') . "'");
        }
    }
    private function _escape(mixed $data) : string
    {
        if (\is_string($data)) {
            return \htmlspecialchars($data, \ENT_QUOTES, 'UTF-8');
        } else if (\is_array($data)) {
            if (\array_walk_recursive($data,function($item, $key) {
                $item = $this->_escape($item);
            }) === false) {
                throw new \Exception("Can't escape parameters of the current request.");
            }
        }
        Service::get("logger")->warn("No escaping rules set for the type: '" . \gettype($data) . "'");
        return $data;
    }

    public function exists(string $key) : bool
    {
        if (\array_key_exists($key, $this->_datas) === false) {
            return false;
        }
        return true;
    }

    public function options(string $key) : ?T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);
    }

    public function get(string $key) : ?T
    {
        if ($this->_method !== Method::GET){
            ## TODO Exception
            throw new \Exception("Can't access '" . Method::GET . "' parameters when on a request of type '" . Server::get('REQUEST_METHOD') . "'");
        }
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);
    }
    public function head(string $key) : ?T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);
    }
    public function post(string $key) : T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);

    }
    public function put(string $key) : T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);

    }
    public function delete(string $key) : T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);

    }
    public function trace(string $key) : T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);

    }
    public function connect(string $key) : T
    {
        $this->_isCurrentRequest();
        return ($this->exists($key) ? $this->_escape($this->_datas[$key]) : null);

    }

    public function all() : array<string, T>
    {
        return $this->_escape($this->_datas);
    }

    protected HttpMethod $_method;
    protected array<string, T> $_datas;
}