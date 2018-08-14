#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <resolv.h>

#define BSD_NOLOOKUP     -1
#define BSD_NOSOCKCREATE -2
#define BSD_NOCONNECT    -3

#define BUFSIZE          1024

int bsd_open(char *hostname, int port);
int bsd_option(int socket, int option);
void bsd_sendstring(int socket, char *string);
