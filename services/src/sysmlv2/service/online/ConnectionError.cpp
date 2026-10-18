//
// Created by Moritz Herzog on 05.01.24.
//

#include <string>
#include <curl/curl.h>

#include "sysmlv2/service/online/ConnectionError.h"

namespace {
    using SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE;
    using namespace SysMLv2::API::EXCEPTIONS;

    /**
     * Builds the single line, human readable message for a connection error. Values without an own text fall back
     * to the description of libcurl.
     */
    std::string describeConnectionError(CONNECTION_ERROR_TYPE errorType) {
        std::string text;
        switch (errorType) {
            case UNSUPPORTED_PROTOCOL:
                text = "The used protocol is unsupported.";
                break;
            case FAILED_INIT:
                text = "Communication initialization Failed.";
                break;
            case URL_FORMAT:
                text = "Wrong URL Format.";
                break;
            case UNKNOWN_PROTOCOL:
                text = "Protocol unknown and thus unsupported.";
                break;
            case COULD_NOT_RESOLVE_PROXY:
                text = "Given proxy could not be resolved.";
                break;
            case COULD_NOT_RESOLVE_HOST:
                text = "Given host could not be resolved.";
                break;
            case COULD_NOT_CONNECT:
                text = "Could not connect to host.";
                break;
            case WIRED_SERVER_REPLY:
                text = "Server reply could not be parsed.";
                break;
            case REMOTE_ACCESS_DENIED:
                text = "Remote access was denied.";
                break;
            case FTP_ACCESS_FAILED:
                text = "Access to ftp server failed.";
                break;
            case FTP_WEIRED_PASS_REPLY:
                text = "Ftp server password reply could not be parsed.";
                break;
            case FTP_ACCEPT_TIMEOUT:
                text = "Accept response of the ftp server timed out.";
                break;
            case FTP_WEIRED_PASV_REPLY:
                text = "Could not get sensible result back from the ftp server.";
                break;
            case FTP_WEIRED_227_FORMAT:
                text = "Could not Parse response from server.";
                break;
            case FTP_CANT_GET_HOST:
                text = "Could not receive Host information.";
                break;
            case HTTP2:
                text = "Error within the HTTP2 framing layer.";
                break;
            case FTP_COULDNT_SET_TYPE:
                text = "Could not set FTP transfer mode to ASCII or byte.";
                break;
            case PARTIAL_FILE:
                text = "The reported filesize did not match the ";
                break;
            case FTP_COULDNT_RETR_FILE:
                text = "Error from the ftp server while receiving the file from the server.";
                break;
            case QUOTE_ERROR:
                text = "Retured error from the sever while sending \"QUOTE\" command.";
                break;
            case HTTP_RETURNED_ERROR:
                text = "Received error code >= 400";
                break;
            case WRITE_ERROR:
                text = "Error received while writing local file.";
                break;
            case UPLOAD_FAILED:
                text = "Failed starting the Upload.";
                break;
            case READ_ERROR:
                text = "An issue occurred while reading a local file.";
                break;
            case OUT_OF_MEMORY:
                text = "Out of memory exception occurred while allocating memory.";
                break;
            case OPERATION_TIMEDOUT:
                text = "The requested operation timed out.";
                break;
            case FTP_PORT_FAILED:
                text = "FTP port command returned an error.";
                break;
            case FTP_COULDNT_USE_REST:
                text = "Command sent to the server, resulted in an error from the sever.";
                break;
            case RANGE_ERROR:
                text = "The server does not support or accept range requests.";
                break;
            case HTTP_POST_ERROR:
                text = "This is an odd error that mainly occurs due to internal confusion.";
                break;
            case SSL_CONNECT_ERROR:
                text = "A problem occurred somewhere in the SSL/TLS handshake.";
                break;
            case BAD_DOWNLOAD_RESUME:
                text = "The download could not be resumed because the specified offset was out of the file boundary.";
                break;
            case FILE_COUNDNT_READ_FILE:
                text = "Requested File could not be opened. This could be the case, if the file path is wrong.";
                break;
            case LDAP_CANNOT_BIND:
                text = "LDAP cannot bind. LDAP bind operation failed.";
                break;
            case LDAP_SEARCH_FAILED:
                text = "LDAP search failed.";
                break;
            case FUNCTION_NOT_FOUND:
                text = "A required ZlibFunction was not found.";
                break;
            case ABORTED_BY_CALLBACK:
                text = "A callback returned was aborted by the system.";
                break;
            case BAD_FUNCTION_ARGUMENT:
                text = "A function was called with a bad argument.";
                break;
            case INTERFACE_FAILED:
                text = "Interface Error, where a specified outgoing interface could not be used.";
                break;
            case TOO_MANY_REDIRECTS:
                text = "Too many redirects.";
                break;
            case UNKNOWN_OPTION:
                text = "An option passed to libcurl is not recognized/known.";
                break;
            case GOT_NOTHING:
                text = "Nothing was retuned by the server, in this case it is considered an error.";
                break;
            case SLL_ENGINE_NOTFOUND:
                text = "The specified crypto engine was not found.";
                break;
            case SSL_ENGINE_SETFAILED:
                text = "Failed setting the selected SSL crypto engine as default.";
                break;
            case SEND_ERROR:
                text = "Failed sending network data.";
                break;
            case RECV_ERROR:
                text = "Failure with receiving network data.";
                break;
            case SSL_CERTPROBLEM:
                text = "Problem with the local client certificate.";
                break;
            case SSL_CIPHER:
                text = "Could not use specified cipher.";
                break;
            case PEER_FAILED_VERIFICATION:
                text = "The remote server's SSL certificate or SSH fingerprint was deemed not OK.";
                break;
            case BAD_CONTENT_ENCODING:
                text = "Unrecognized transfer encoding.";
                break;
            case FILE_SIZE_EXCEEDED:
                text = "Maximum file size exceeded.";
                break;
            case USE_SSL_FAILED:
                text = "Requested FTP SSL level failed.";
                break;
            case SEND_FAIL_REWIND:
                text = "When doing a send operation DT-App had to rewind the data to retransmit, but the rewinding operation failed.";
                break;
            case SSL_ENGINE_INITFAILED:
                text = "Initiating the SSL Engine failed.";
                break;
            case LOGIN_DENIED:
                text = "The remote server denied the login.";
                break;
            case TFTP_NOTFOUND:
                text = "File not found on TFTP server.";
                break;
            case TFTP_PERM:
                text = "Permission problem on TFTP server.";
                break;
            case REMOTE_DISK_FULL:
                text = "Out of disk space on the server.";
                break;
            case TFTP_ILLEGAL:
                text = "Illegal TFTP operation.";
                break;
            case TFTP_UNKNOWNID:
                text = "Unknown TFTP transfer ID.";
                break;
            case REMOTE_FILE_EXITIS:
                text = "File already exists and is not overwritten.";
                break;
            case TFTP_NOSUCHUSER:
                text = "This error should never be returned by a properly functioning TFTP server.";
                break;
            case SSL_CACERT_BADFILE:
                text = "";
                break;
            case REMOTE_FILE_NOT_FOUND:
                text = "The resource referenced in the URL does not exist.";
                break;
            case SSH:
                text = "An unspecified error occurred during the SSH session.";
                break;
            case SSL_SHUTDOWN_FAILED:
                text = "Failed to shut down the SSL connection.";
                break;
            case AGAIN:
                text = "Socket is not ready for send/recv wait till it's ready and try again.";
                break;
            case SSL_CRL_BADFILE:
                text = "Failed to load CRL file.";
                break;
            case SSL_ISSUER_ERROR:
                text = "Issuer check failed";
                break;
            case FTP_PRET_FAILED:
                text = "The FTP server does not understand the PRET command at all or does not support the given argument.";
                break;
            case RTSP_CSEQ_ERROR:
                text = "Mismatch of RTSP CSeq numbers.";
                break;
            case RTSP_SESSION_ERROR:
                text = "Mismatch of RTSP Session Identifiers.";
                break;
            case FTP_BAS_DILE_LIST:
                text = "Unable to parse FTP file list (during FTP wildcard downloading).";
                break;
            case CHUNK_FAILED:
                text = "Chunk callback reported error.";
                break;
            case NO_CONNECTION_AVAILABLE:
                text = "";
                break;
            case SSK_PINNEDPUBKEYNOTMATCH:
                text = "Failed to match the pinned key specified with CURLOPT_PINNEDPUBLICKEY.";
                break;
            case SSL_INVALIDCERTSTATUS:
                text = "Status returned failure when asked with CURLOPT_SSL_VERIFYSTATUS.";
                break;
            case HTTP2_STREAM:
                text = "Stream error in the HTTP/2 framing layer.";
                break;
            case RECURSIVE_API_CALL:
                text = "An API function was called from inside a callback.";
                break;
            case AUTH_ERROR:
                text = "An authentication function returned an error.";
                break;
            case HTTP3:
                text = "A problem was detected in the HTTP/3 layer.";
                break;
            case QUIC_CONNECT_ERROR:
                text = "QUIC connection error. This error may be caused by an SSL library error.";
                break;
            case PROXY:
                text = "Proxy handshake error.";
                break;
            case SSL_CLIENTCERT:
                text = "SSL Client Certificate required.";
                break;
            case UNRECOVERABLE_POLL:
                text = "An internal call to poll() or select() returned error that is not recoverable.";
                break;
            case TOO_LARGE:
                text = "A value or data field grew larger than allowed.";
                break;
            default:
                break;
        }

        if (text.empty())
            text = curl_easy_strerror(static_cast<CURLcode>(errorType));
        return "Error in the network stack: " + text + " (error code " + std::to_string(static_cast<int>(errorType)) + ")";
    }
}

namespace SysMLv2::API::EXCEPTIONS {
    ConnectionError::ConnectionError(CONNECTION_ERROR_TYPE errorType)
    : runtime_error(describeConnectionError(errorType)), ErrorType(errorType) {
    }

    CONNECTION_ERROR_TYPE ConnectionError::errorType() const noexcept {
        return ErrorType;
    }
}
