#include "user.h"
#include "Server.h"
#include "unihead.h"

char buf[bufsize + 1];

int main()
{
    Server server;
    server.Bind();
    server.Listen();
    fcntl(server.sock, F_SETFL, O_NONBLOCK | fcntl(server.sock, F_GETFL, 0));
    cout << "server is ready!\n"
         << "=====================waiting for users=======================" << endl;
    User ** onlineusers = new User * [server.maxsize];
    int online = 0;
    fd_set readset;
    int ret;
    User* thisuser;
    struct timeval tv;
    int maxfdp;
//服务器主循环
    cout << "listen sock:" << server.sock << endl;
    while (1)
    {   
        cout << "online:" << online << endl;
        FD_ZERO(&readset);
//向readset中塞入用户和服务器套接字;为了简洁,不考虑writeset
        maxfdp = server.sock;
        FD_SET(server.sock, &readset);
        for(int i=0; i<online; i++){
//通过此次user遍历发送字符串
            thisuser = onlineusers[i];
            if(thisuser->out != ""){
                send(thisuser->sock, thisuser->out.c_str(), thisuser->out.size()+1, 0);
                thisuser->out = "";
            }


            FD_SET(thisuser->sock, &readset);
            maxfdp = thisuser->sock > maxfdp ? thisuser->sock : maxfdp;
        }
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        if((ret = select(maxfdp+1, &readset, NULL, NULL, &tv)) == -1)
            Server::Error("select failed");
        
        if(ret == 0){
            cout << "time out!" << endl;
            continue;
        }
//用户可读，则是有信息发送过来
        for(int i=0; i<online; i++){
            thisuser = onlineusers[i];
            cout << thisuser->sock << " is this user's sock" << endl;
            if(FD_ISSET(thisuser->sock, &readset)){
                thisuser->Recv();
//最关键的就是对用户的每个特殊的消息做出正确的反应
                if(thisuser->get == ""){
                    delete thisuser;
                    for(int j=i; j<online-1; j++)
                        onlineusers[j] = onlineusers[j+1];
                    online--;
                }
                cout << "thisuser->get:" << thisuser->get << endl;
            }
        }
//服务器可读，即有新的连接请求发生
        if(FD_ISSET(server.sock, &readset)){
            cout << "new user!" << endl;
            User* newuser = new User;
            if((newuser->sock = accept(server.sock, NULL, NULL)) == -1)
                Server::Error("accept failed");
            
            fcntl(newuser->sock, F_SETFL, O_NONBLOCK | fcntl(newuser->sock, F_GETFL, 0));
            onlineusers[online] = newuser;
            online++;
        }
    }
}
