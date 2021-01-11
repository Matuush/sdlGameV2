#include "UdpCom.h"

UdpCom::UdpCom(char *ipT, int portT)
{
    ip = ipT;
    port = portT;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    out = socket(AF_INET, SOCK_DGRAM, 0);
}
UdpCom::close()
{
    closesocket(out);
}
UdpCom::start()
{
    WORD version = MAKEWORD(2, 2);
    WSADATA data;
    WSAStartup(version, &data);
}
UdpCom::stop()
{
    WSACleanup();
}
UdpCom::send(char *buf)
{
    std::string s(buf);
    sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
}
