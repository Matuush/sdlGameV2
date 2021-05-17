#pragma once
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class UdpCom {
public:
    const char* ip;
    int port;

    UdpCom(const char* ipT, int portT) : ip(ipT), port(portT) {
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        inet_pton(AF_INET, ip, &server.sin_addr);
        out = socket(AF_INET, SOCK_DGRAM, 0);
    }

    void send(const char* buf) {
        std::string s(buf);
        int temp = sendto(out, s.c_str(), s.size(), 0, (sockaddr*)&server, sizeof(server));
        if (temp == SOCKET_ERROR) std::cout << "COCKET error\n";
    }
    static void start() {
        WORD version = MAKEWORD(2, 2);
        WSADATA data;
        int temp = WSAStartup(version, &data);
        if (temp != 0) std::cout << "wincock error\n";
    }
    static void stop() { WSACleanup(); }
    void close() { closesocket(out); }
protected:
    WORD version;
    SOCKET out;
    sockaddr_in server;
};