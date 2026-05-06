 #include <unistd.h>
 #include <string.h> 
 #include <stdio.h>
 #include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>


int ids[1024], id, sfd, mx;
char sb[600000],mb[600000], buf[1024][600000];
fd_set fds;

void err(char *s) {write(2, s, strlen(s));exit(1);}

void cast(int ex)
{
    for (int i = 0; i < mx; i++)
        if ()
}