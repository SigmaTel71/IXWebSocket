#include "IXSocketSchannel.h"
/*
 *  IXSocketWinCrypt.h
 *  Author: Vitaly Orekhov
 *  Copyright (c) 2017-2026 Machine Zone, Inc. All rights reserved.
 */
#ifdef IXWEBSOCKET_USE_SCHANNEL

namespace ix
{
    SocketSchannel::SocketSchannel(const SocketTLSOptions& tlsOptions, int fd)
        : Socket(fd)
        , _tlsOptions(tlsOptions)
    {
        std::call_once(_schannelInitFlag, &SocketSchannel::schannelInitialize, this);
    }

    SocketSchannel::~SocketSchannel()
    {
        SocketSchannel::close();
    }
    
    bool SocketSchannel::accept(std::string& errMsg)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        return false;
    }
    
    bool SocketSchannel::connect(const std::string& host,
                                 int port,
                                 std::string& errMsg,
                                 const CancellationRequest& isCancellationRequested)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        return false;
    }
    
    void SocketSchannel::close()
    {
        std::lock_guard<std::mutex> lock(_mutex);

    }
    
    ssize_t SocketSchannel::send(char* buffer, size_t length)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        return -1;
    }
    
    ssize_t SocketSchannel::recv(void* buffer, size_t length)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        return -1;
    }
        
    void SocketSchannel::schannelInitialize()
    {
        std::lock_guard<std::mutex> lock(_mutex);

        SCH_CREDENTIALS creds;
        creds.dwVersion = SCH_CREDENTIALS_VERSION;
        creds.dwFlags = SCH_CRED_AUTO_CRED_VALIDATION | SCH_USE_STRONG_CRYPTO;
        
        if (this->_tlsOptions.disable_hostname_validation)
            creds.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK; // I don't think it's this one
    }
} // namespace ix

#endif // IXWEBSOCKET_USE_SCHANNEL