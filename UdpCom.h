#pragma once
#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class UdpCom {
public:
    const char* ip;
    int port;

    UdpCom(const char* ipT, int portT);

    void send(const char* message);
    static void start();
    static void stop();
    void close();
protected:
    WORD version;
    SOCKET out;
    sockaddr_in server;
};