#ifndef SERVER_H
#define SERVER_H
#include "unihead.h"

class Server
{
public:
    int sock;
    struct sockaddr_in servaddr;
    int port;
    int maxsize;

    Server(int maxmem = 50, int po = 9990) : maxsize(maxmem), port(po) {}
    ~Server() {}
    static void Error(const char *);
    void Bind();
    void Listen();
};

#endif