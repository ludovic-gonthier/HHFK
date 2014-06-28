<?hh //strict
namespace HHFK\Debug;

class Debugger
{
    public function dump(mixed $value) : void
    {
        echo "<pre>", \var_dump($value), "</pre>";
    }

    public function context() : void
    {
        echo "<pre>", \debug_backtrace(), "</pre>";
    }

    public function trace() : void
    {
        \debug_print_backtrace();
    }
}