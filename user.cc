#include "user.h"

void User::Recv()
{
    memset(buf, 0, sizeof(buf));
    int nret = recv(sock, buf, bufsize, 0);
    if (nret == 0)
    {
        get = "";
        return;
    }
    out = get = buf;
}
