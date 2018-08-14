#include <stdio.h>
#include <signal.h>

#include "bsd.h"

int s, child, i, j, bold = 0, frames, backendpid;
FILE *fp;
char buff[1024],filename[100], host[100];

void shutd(char *s)
{
   kill(child,SIGTERM);
   if (s) printf("<B>Error:</B> <I> %s</I>\n");
   printf("<BR></PRE></BODY></HTML>\n"); 
   close(s);
   exit(0);
}

int clientdied(int sig)
{
   shutd("Client died");
}

int parentdied(int sig)
{
  fclose(fp);
  unlink(filename);
  exit(0);
}

int main(int argc, char **argv)
{
  printf("HTTP/1.0 200 OK\nContent-type: text/html\n\n");
  printf("<HTML><BODY><PRE>\n");

  /* Kolla argument */
  if (argc != 2) {
    shutd("Wrong syntax");
  }
  sprintf(filename,"/tmp/%s.in",argv[1]);

  s = bsd_open("poledra.coyote.org", 4201);
  if (s < 0) shutd("Could not open BSD Socket");

  if ( (child = fork()) == -1 ) shutd("Can't fork subprocess!");

  if (!child) {
    signal(SIGTERM,(void (*)())clientdied);
    signal(SIGPIPE,(void (*)())clientdied);
    while (1) {
      usleep(100);
      fflush(stdout);
      i = recv(s,buff,1024,0);
      if (i > 0) {
        for (j = 0; j < i; j++)
        if (buff[j] == '\n') printf("<BR>");
        else if (buff[j] == '<') printf("&lt;");
        else if (buff[j] == '>') printf("&gt;");
        else if ((buff[j] == 0x1b) && (buff[j+1] == '[')) /* ANSI */ {
          j += 2;
          if ( (buff[j] == '0') && (bold)) {
            printf("</B>");
            bold = 0;
          } else if ( (buff[j] == '1') && !(bold)) {
            printf("<B>");
            bold = 1;
          }
          j++;
        } else printf("%c",buff[j]);
      } else if ( errno != EWOULDBLOCK )
          shutd(NULL);
    }
  } else {
    signal(SIGTERM,(void (*)())parentdied);
    while (1)
      if ( (fp = fopen(filename, "r")) != NULL ) {
         while ( (i = fread(buff,1,1024,fp)) != 0)
            send(s,buff,i,0);
         close(fp);
         unlink(filename);
      }
   }
}
