/*
 *  IXSocketWinCrypt.h
 *  Author: Vitaly Orekhov
 *  Copyright (c) 2017-2026 Machine Zone, Inc. All rights reserved.
 */
#ifdef IXWEBSOCKET_USE_SCHANNEL

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <basetsd.h>
#include <wincrypt.h>
#include <ws2tcpip.h>
#include <ws2def.h>
#include <schannel.h>
#include <schnlsp.h>
#include <security.h>

#include "IXCancellationRequest.h"
#include "IXSocket.h"
#include "IXSocketTLSOptions.h"

#include <mutex>

namespace ix
{
    class SocketSchannel final : public Socket
	{
    public:
        SocketSchannel(const SocketTLSOptions& tlsOptions, int fd = -1);
        ~SocketSchannel();

		virtual bool accept(std::string& errMsg) final;

        virtual bool connect(const std::string& host,
                             int port,
                             std::string& errMsg,
                             const CancellationRequest& isCancellationRequested) final;
        virtual void close() final;

        virtual ssize_t send(char* buffer, size_t length) final;
        virtual ssize_t recv(void* buffer, size_t length) final;
    private:
        void schannelInitialize();

        std::mutex _mutex;
        static std::once_flag _schannelInitFlag;
        
        CredHandle _hCred;
        SocketTLSOptions _tlsOptions;
	};
}

#endif // IXWEBSOCKET_USE_SCHANNEL