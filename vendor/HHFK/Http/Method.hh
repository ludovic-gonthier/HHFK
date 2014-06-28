<?hh // strict
namespace HHFK\Http;

type HttpMethod = string;
/**
 * Interface used to define the Method allowed by the HTTP/1.1 rfc
 */
interface Method
{
    /**
     * Methods allowed by HTTP/1.1
     * as declared on the rfc
     * @see http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
     */
    const HttpMethod
        OPTIONS = 'OPTIONS',
        GET     = 'GET',
        HEAD    = 'HEAD',
        POST    = 'POST',
        PUT     = 'PUT',
        DELETE  = 'DELETE',
        TRACE   = 'TRACE',
        CONNECT = 'CONNECT'
    ;
}