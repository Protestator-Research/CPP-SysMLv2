//
// Created by Moritz Herzog on 05.01.24.
//

#pragma once

#include <stdexcept>
#include "../sysmlv2service_global.h"

#include "../sysmlv2service_global.h"

namespace SysMLv2::API::EXCEPTIONS {
    enum SYSMLV2SERVICE_EXPORT CONNECTION_ERROR_TYPE {
        UNSUPPORTED_PROTOCOL = 1,
        FAILED_INIT,
        URL_FORMAT,
        UNKNOWN_PROTOCOL,
        COULD_NOT_RESOLVE_PROXY,
        COULD_NOT_RESOLVE_HOST,
        COULD_NOT_CONNECT,
        WIRED_SERVER_REPLY,
        REMOTE_ACCESS_DENIED,
        FTP_ACCESS_FAILED,
        FTP_WEIRED_PASS_REPLY,
        FTP_ACCEPT_TIMEOUT,
        FTP_WEIRED_PASV_REPLY,
        FTP_WEIRED_227_FORMAT,
        FTP_CANT_GET_HOST,
        HTTP2,
        FTP_COULDNT_SET_TYPE,
        PARTIAL_FILE,
        FTP_COULDNT_RETR_FILE,
        QUOTE_ERROR = 21,
        HTTP_RETURNED_ERROR,
        WRITE_ERROR,
        UPLOAD_FAILED = 25,
        READ_ERROR,
        OUT_OF_MEMORY,
        OPERATION_TIMEDOUT,
        FTP_PORT_FAILED = 30,
        FTP_COULDNT_USE_REST,
        RANGE_ERROR = 33,
        HTTP_POST_ERROR,
        SSL_CONNECT_ERROR,
        BAD_DOWNLOAD_RESUME,
        FILE_COUNDNT_READ_FILE,
        LDAP_CANNOT_BIND,
        LDAP_SEARCH_FAILED,
        FUNCTION_NOT_FOUND = 41,
        ABORTED_BY_CALLBACK,
        BAD_FUNCTION_ARGUMENT,
        INTERFACE_FAILED = 45,
        TOO_MANY_REDIRECTS = 47,
        UNKNOWN_OPTION,
        GOT_NOTHING = 52,
        SLL_ENGINE_NOTFOUND,
        SSL_ENGINE_SETFAILED,
        SEND_ERROR,
        RECV_ERROR,
        SSL_CERTPROBLEM,
        SSL_CIPHER,
        PEER_FAILED_VERIFICATION,
        BAD_CONTENT_ENCODING,
        FILE_SIZE_EXCEEDED = 63,
        USE_SSL_FAILED,
        SEND_FAIL_REWIND,
        SSL_ENGINE_INITFAILED,
        LOGIN_DENIED,
        TFTP_NOTFOUND,
        TFTP_PERM,
        REMOTE_DISK_FULL,
        TFTP_ILLEGAL,
        TFTP_UNKNOWNID,
        REMOTE_FILE_EXITIS,
        TFTP_NOSUCHUSER,
        SSL_CACERT_BADFILE = 77,
        REMOTE_FILE_NOT_FOUND,
        SSH,
        SSL_SHUTDOWN_FAILED,
        AGAIN,
        SSL_CRL_BADFILE,
        SSL_ISSUER_ERROR,
        FTP_PRET_FAILED,
        RTSP_CSEQ_ERROR,
        RTSP_SESSION_ERROR,
        FTP_BAS_DILE_LIST,
        CHUNK_FAILED,
        NO_CONNECTION_AVAILABLE,
        SSK_PINNEDPUBKEYNOTMATCH,
        SSL_INVALIDCERTSTATUS,
        HTTP2_STREAM,
        RECURSIVE_API_CALL,
        AUTH_ERROR,
        HTTP3,
        QUIC_CONNECT_ERROR,
        PROXY,
        SSL_CLIENTCERT,
        UNRECOVERABLE_POLL,
        TOO_LARGE
    };
    class SYSMLV2SERVICE_EXPORT ConnectionError : public std::runtime_error {
    public:
        ConnectionError() = delete;
        ConnectionError(SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE errorType);

        const char * what() const noexcept override;
    private:
        CONNECTION_ERROR_TYPE ErrorType;
    };
}
