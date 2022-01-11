#ifndef BA7EB1C8_C1B3_4E68_94C8_DDC9728431BF
#define BA7EB1C8_C1B3_4E68_94C8_DDC9728431BF
#include "unihead.h"
class User
{
private:
    string name;
    string password;
    User *next;

public:
    string out;
    string get;
    int sock;
    User() : next(NULL) {}
    ~User() {}
    void Recv();
};

#endif /* BA7EB1C8_C1B3_4E68_94C8_DDC9728431BF */
