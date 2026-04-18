#include "IXTest.h"
#include "catch.hpp"
#include <ixwebsocket/IXUrlParser.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketServer.h>

using namespace ix;

TEST_CASE("IPv6")
{
    SECTION("URL parser strips brackets from IPv6 host and parses port")
    {
        std::string protocol, host, path, query;
        int port = -1;

        bool ok = UrlParser::parse("ws://[::1]:9001/chat", protocol, host, path, query, port);
        CHECK(ok);
        CHECK(protocol == "ws");
        CHECK(host == "::1");
        CHECK(port == 9001);
        CHECK(path == "/chat");
    }

    SECTION("URL parser handles IPv6 without port")
    {
        std::string protocol, host, path, query;
        int port = -1;

        bool ok = UrlParser::parse("ws://[::1]/", protocol, host, path, query, port);
        CHECK(ok);
        CHECK(protocol == "ws");
        CHECK(host == "::1");
        CHECK(port == 80);
    }

    SECTION("Listening on ::1 works with AF_INET6 works")
    {
        int port = getFreePort();
        ix::WebSocketServer server(port,
                                   "::1",
                                   SocketServer::kDefaultTcpBacklog,
                                   SocketServer::kDefaultMaxConnections,
                                   WebSocketServer::kDefaultHandShakeTimeoutSecs,
                                   AF_INET6);

        auto res = server.listen();
        CHECK(res.first);
        server.start();
        server.stop();
    }
}
