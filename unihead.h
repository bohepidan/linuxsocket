#ifndef UNIHEAD_H
#define UNIHEAD_H

#include <sys/select.h>
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
using namespace std;
#define bufsize 1024
extern char buf[bufsize + 1];
#endif