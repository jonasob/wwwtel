#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "bsd.h"

int bsd_open(char *hostname, int port)
{
        int sockfd;
        struct hostent *hostinfo;
        struct sockaddr_in remote_address;

        if ((hostinfo = (struct hostent *)gethostbyname(hostname)) == NULL)
                return(BSD_NOLOOKUP);
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
                return(BSD_NOSOCKCREATE);

        remote_address.sin_family = AF_INET;
        remote_address.sin_port = htons(port);
        remote_address.sin_addr = *((struct in_addr *)hostinfo->h_addr);
        memset(&remote_address.sin_zero, 0, 8);

        if (connect(sockfd, (struct sockaddr *)&remote_address,
            sizeof(struct sockaddr)) == -1)
                return(BSD_NOCONNECT);

        return(sockfd);
}

void bsd_sendstring(int socket,char *string)
{
        int len, sent = 0;
        char buf[BUFSIZE];

        len = strlen(string);
        strcpy(buf,string);
        buf[len] = '\r';
        buf[len + 1] = '\n';
        while(sent < len + 2)
                sent = send(socket, buf, len + 2, 0);
}

int bsd_option(int socket, int option)
{
   return(fcntl(socket,F_SETFL,option));
}
