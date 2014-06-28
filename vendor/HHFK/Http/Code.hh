<?hh // strict
namespace HHFK\Http;

newtype HttpCode = string;

interface Code
{
    const HttpCode
    // Informational 1xx
        HHTP_CONTINUE                       = '100 Continue',
        HHTP_SWITCHING_PROTOCOLS            = '101 Switching Protocols',

    // Successful 2xx
        HHTP_OK                             = '200 OK',
        HHTP_CREATED                        = '201 Created',
        HHTP_ACCEPTED                       = '202 Accepted',
        HHTP_NON_AUTHORITATIVE_INFORMATION  = '203 Non-Authoritative Information',
        HHTP_NO_CONTENT                     = '204 No Content',
        HHTP_RESET_CONTENT                  = '205 Reset Content',
        HHTP_PARTIAL_CONTENT                = '206 Partial Content',

    // Redirection 3xx
        HHTP_MULTIPLE_CHOICES               = '300 Multiple Choices',
        HHTP_MOVED_PERMANENTLY              = '301 Moved Permanently',
        HHTP_FOUND                          = '302 Found',
        HHTP_SEE_OTHER                      = '303 See Other',
        HHTP_NOT_MODIFIED                   = '304 Not Modified',
        HHTP_USE_PROXY                      = '305 Use Proxy',
        HHTP_UNUSED                         = '306 (Unused)',
        HHTP_TEMPORARY_REDIRECT             = '307 Temporary Redirect',

    // Client Error 4xx
        HHTP_BAD_REQUEST                    = '400 Bad Request',
        HHTP_UNAUTHORIZED                   = '401 Unauthorized',
        HHTP_PAYMENT_REQUIRED               = '402 Payment Required',
        HHTP_FORBIDDEN                      = '403 Forbidden',
        HHTP_NOT_FOUND                      = '404 Not Found',
        HHTP_METHOD_NOT_ALLOWED             = '405 Method Not Allowed',
        HHTP_NOT_ACCEPTABLE                 = '406 Not Acceptable',
        HHTP_PROXY_AUTHENTICATION_REQUIRED  = '407 Proxy Authentication Required',
        HHTP_REQUEST_TIMEOUT                = '408 Request Timeout',
        HHTP_CONFLICT                       = '409 Conflict',
        HHTP_GONE                           = '410 Gone',
        HHTP_LENGTH_REQUIRED                = '411 Length Required',
        HHTP_PRECONDITION_FAILED            = '412 Precondition Failed',
        HHTP_REQUEST_ENTITY_TOO_LARGE       = '413 Request Entity Too Large',
        HHTP_REQUEST_URI_TOO_LONG           = '414 Request-URI Too Long',
        HHTP_UNSUPPORTED_MEDIA_TYPE         = '415 Unsupported Media Type',
        HHTP_REQUESTED_RANGE_NOT_SATISFIABLE= '416 Requested Range Not Satisfiable',
        HHTP_EXPECTATION_FAILED             = '417 Expectation Failed',

    // Server Error 5xx
        HHTP_INTERNAL_SERVER_ERROR          = '500 Internal Server Error',
        HHTP_NOT_IMPLEMENTED                = '501 Not Implemented',
        HHTP_BAD_GATEWAY                    = '502 Bad Gateway',
        HHTP_SERVICE_UNAVAILABLE            = '503 Service Unavailable',
        HHTP_GATEWAY_TIMEOUT                = '504 Gateway Timeout',
        HHTP_HTTP_VERSION_NOT_SUPPORTED     = '505 HTTP Version Not Supported'
    ;
}