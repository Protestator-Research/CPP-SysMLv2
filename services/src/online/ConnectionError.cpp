//
// Created by Moritz Herzog on 05.01.24.
//

#include "ConnectionError.h"
#include <string>

namespace SysMLv2::API::EXCEPTIONS {
    ConnectionError::ConnectionError(CONNECTION_ERROR_TYPE errorType)
    : runtime_error("") {
        ErrorType = errorType;
    }

    const char *ConnectionError::what() const noexcept {
        std::string returnValue = "Error in the Networkstack:\r\n";
        switch (ErrorType) {
            case UNSUPPORTED_PROTOCOL:
                returnValue += "The used protocol is unsupported.";
                break;
            case FAILED_INIT:
                returnValue += "Communication initialization Failed.";
                break;
            case URL_FORMAT:
                returnValue += "Wrong URL Format.";
                break;
            case UNKNOWN_PROTOCOL:
                returnValue += "Protocol unknown and thus unsupported.";
                break;
            case COULD_NOT_RESOLVE_PROXY:
                returnValue += "Given proxy could not be resolved.";
                break;
            case COULD_NOT_RESOLVE_HOST:
                returnValue += "Given host could not be resolved.";
                break;
            case COULD_NOT_CONNECT:
                returnValue += "Could not connect to host.";
                break;
            case WIRED_SERVER_REPLY:
                returnValue += "Server reply could not be parsed.";
                break;
            case REMOTE_ACCESS_DENIED:
                returnValue += "Remote access was denied.";
                break;
            case FTP_ACCESS_FAILED:
                returnValue += "Access to ftp server failed.";
                break;
            case FTP_WEIRED_PASS_REPLY:
                returnValue += "Ftp server password reply could not be parsed.";
                break;
            case FTP_ACCEPT_TIMEOUT:
                returnValue += "Accept response of the ftp server timed out.";
                break;
            case FTP_WEIRED_PASV_REPLY:
                returnValue += "Could not get sensible result back from the ftp server.";
                break;
            case FTP_WEIRED_227_FORMAT:
                returnValue += "Could not Parse response from server.";
                break;
            case FTP_CANT_GET_HOST:
                returnValue += "Could not receive Host information.";
                break;
            case HTTP2:
                returnValue += "Error within the HTTP2 framing layer.";
                break;
            case FTP_COULDNT_SET_TYPE:
                returnValue += "Could not set FTP transfer mode to ASCII or byte.";
                break;
            case PARTIAL_FILE:
                returnValue += "The reported filesize did not match the ";
                break;
            case FTP_COULDNT_RETR_FILE:
                returnValue += "Error from the ftp server while receiving the file from the server.";
                break;
            case QUOTE_ERROR:
                returnValue += "Retured error from the sever while sending \"QUOTE\" command.";
                break;
            case HTTP_RETURNED_ERROR:
                returnValue += "Received error code >= 400";
                break;
            case WRITE_ERROR:
                returnValue += "Error received while writing local file.";
                break;
            case UPLOAD_FAILED:
                returnValue += "Failed starting the Upload.";
                break;
            case READ_ERROR:
                returnValue += "An issue occurred while reading a local file.";
                break;
            case OUT_OF_MEMORY:
                returnValue += "Out of memory exception occurred while allocating memory.";
                break;
            case OPERATION_TIMEDOUT:
                returnValue += "The requested operation timed out.";
                break;
            case FTP_PORT_FAILED:
                returnValue += "FTP port command returned an error.";
                break;
            case FTP_COULDNT_USE_REST:
                returnValue += "Command sent to the server, resulted in an error from the sever.";
                break;
            case RANGE_ERROR:
                returnValue += "The server does not support or accept range requests.";
                break;
            case HTTP_POST_ERROR:
                returnValue += "This is an odd error that mainly occurs due to internal confusion.";
                break;
            case SSL_CONNECT_ERROR:
                returnValue += "A problem occurred somewhere in the SSL/TLS handshake.";
                break;
            case BAD_DOWNLOAD_RESUME:
                returnValue += "The download could not be resumed because the specified offset was out of the file boundary.";
                break;
            case FILE_COUNDNT_READ_FILE:
                returnValue += "Requested File could not be opened. This could be the case, if the file path is wrong.";
                break;
            case LDAP_CANNOT_BIND:
                returnValue += "LDAP cannot bind. LDAP bind operation failed.";
                break;
            case LDAP_SEARCH_FAILED:
                returnValue += "LDAP search failed.";
                break;
            case FUNCTION_NOT_FOUND:
                returnValue += "A required ZlibFunction was not found.";
                break;
            case ABORTED_BY_CALLBACK:
                returnValue += "A callback returned was aborted by the system.";
                break;
            case BAD_FUNCTION_ARGUMENT:
                returnValue += "A function was called with a bad argument.";
                break;
            case INTERFACE_FAILED:
                returnValue += "Interface Error, where a specified outgoing interface could not be used.";
                break;
            case TOO_MANY_REDIRECTS:
                returnValue += "Too many redirects.";
                break;
            case UNKNOWN_OPTION:
                returnValue += "An option passed to libcurl is not recognized/known.";
                break;
            case GOT_NOTHING:
                returnValue += "Nothing was retuned by the server, in this case it is considered an error.";
                break;
            case SLL_ENGINE_NOTFOUND:
                returnValue += "The specified crypto engine was not found.";
                break;
            case SSL_ENGINE_SETFAILED:
                returnValue += "Failed setting the selected SSL crypto engine as default.";
                break;
            case SEND_ERROR:
                returnValue += "Failed sending network data.";
                break;
            case RECV_ERROR:
                returnValue += "Failure with receiving network data.";
                break;
            case SSL_CERTPROBLEM:
                returnValue += "Problem with the local client certificate.";
                break;
            case SSL_CIPHER:
                returnValue += "Could not use specified cipher.";
                break;
            case PEER_FAILED_VERIFICATION:
                returnValue += "The remote server's SSL certificate or SSH fingerprint was deemed not OK.";
                break;
            case BAD_CONTENT_ENCODING:
                returnValue += "Unrecognized transfer encoding.";
                break;
            case FILE_SIZE_EXCEEDED:
                returnValue += "Maximum file size exceeded.";
                break;
            case USE_SSL_FAILED:
                returnValue += "Requested FTP SSL level failed.";
                break;
            case SEND_FAIL_REWIND:
                returnValue += "When doing a send operation DT-App had to rewind the data to retransmit, but the rewinding operation failed.";
                break;
            case SSL_ENGINE_INITFAILED:
                returnValue += "Initiating the SSL Engine failed.";
                break;
            case LOGIN_DENIED:
                returnValue += "The remote server denied the login.";
                break;
            case TFTP_NOTFOUND:
                returnValue += "File not found on TFTP server.";
                break;
            case TFTP_PERM:
                returnValue += "Permission problem on TFTP server.";
                break;
            case REMOTE_DISK_FULL:
                returnValue += "Out of disk space on the server.";
                break;
            case TFTP_ILLEGAL:
                returnValue += "Illegal TFTP operation.";
                break;
            case TFTP_UNKNOWNID:
                returnValue += "Unknown TFTP transfer ID.";
                break;
            case REMOTE_FILE_EXITIS:
                returnValue += "File already exists and is not overwritten.";
                break;
            case TFTP_NOSUCHUSER:
                returnValue += "This error should never be returned by a properly functioning TFTP server.";
                break;
            case SSL_CACERT_BADFILE:
                returnValue += "";
                break;
            case REMOTE_FILE_NOT_FOUND:
                returnValue += "The resource referenced in the URL does not exist.";
                break;
            case SSH:
                returnValue += "An unspecified error occurred during the SSH session.";
                break;
            case SSL_SHUTDOWN_FAILED:
                returnValue += "Failed to shut down the SSL connection.";
                break;
            case AGAIN:
                returnValue += "Socket is not ready for send/recv wait till it's ready and try again.";
                break;
            case SSL_CRL_BADFILE:
                returnValue += "Failed to load CRL file.";
                break;
            case SSL_ISSUER_ERROR:
                returnValue += "Issuer check failed";
                break;
            case FTP_PRET_FAILED:
                returnValue += "The FTP server does not understand the PRET command at all or does not support the given argument.";
                break;
            case RTSP_CSEQ_ERROR:
                returnValue += "Mismatch of RTSP CSeq numbers.";
                break;
            case RTSP_SESSION_ERROR:
                returnValue += "Mismatch of RTSP Session Identifiers.";
                break;
            case FTP_BAS_DILE_LIST:
                returnValue += "Unable to parse FTP file list (during FTP wildcard downloading).";
                break;
            case CHUNK_FAILED:
                returnValue += "Chunk callback reported error.";
                break;
            case NO_CONNECTION_AVAILABLE:
                returnValue += "";
                break;
            case SSK_PINNEDPUBKEYNOTMATCH:
                returnValue += "Failed to match the pinned key specified with CURLOPT_PINNEDPUBLICKEY.";
                break;
            case SSL_INVALIDCERTSTATUS:
                returnValue += "Status returned failure when asked with CURLOPT_SSL_VERIFYSTATUS.";
                break;
            case HTTP2_STREAM:
                returnValue += "Stream error in the HTTP/2 framing layer.";
                break;
            case RECURSIVE_API_CALL:
                returnValue += "An API function was called from inside a callback.";
                break;
            case AUTH_ERROR:
                returnValue += "An authentication function returned an error.";
                break;
            case HTTP3:
                returnValue += "A problem was detected in the HTTP/3 layer.";
                break;
            case QUIC_CONNECT_ERROR:
                returnValue += "QUIC connection error. This error may be caused by an SSL library error.";
                break;
            case PROXY:
                returnValue += "Proxy handshake error.";
                break;
            case SSL_CLIENTCERT:
                returnValue += "SSL Client Certificate required.";
                break;
            case UNRECOVERABLE_POLL:
                returnValue += "An internal call to poll() or select() returned error that is not recoverable.";
                break;
            case TOO_LARGE:
                returnValue += "A value or data field grew larger than allowed.";
                break;
        }
        returnValue += "\r\nError Code: ";
        returnValue += std::to_string(ErrorType);
        return new char;//returnValue.c_str();
    }


}