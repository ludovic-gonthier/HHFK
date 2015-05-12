<?hh //strict
namespace HHFK\Debug;

## TODO, always load debugger but only effective function call when in debugging mode
class Debugger
{
    public function dump(mixed $value) : this
    {
        echo "<pre>", \var_dump($value), "</pre>";
        return $this;
    }

    public function context() : this
    {
        echo "<pre>", \debug_backtrace(), "</pre>";
        return $this;
    }

    public function trace() : this
    {
        \debug_print_backtrace();
        return $this;
    }
}