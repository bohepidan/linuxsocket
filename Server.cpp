#include "Server.h"
void Server::Error(const char *message)
{
    cout << message << ":\n"
         << strerror(errno) << "(errno:" << errno << ")" << endl;
    exit(1);
}

void Server::Bind()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        Error("create listen socket error");

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        Error("bind error");
}

void Server::Listen()
{
    if (listen(sock, maxsize) == -1)
        Error("listen error");
}
