#include <iostream>
#include <string>
#include <W2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class UdpCom
{
public:
    char *ip;
    int port;
    UdpCom(char *ipT, int portT);
    void send(char *message);
    static void start();
    static void stop();
    void close();
protected:
    WSDATA socketInfo;
    WORD version;
    SOCKET out;
    sockaddr_in server;
}