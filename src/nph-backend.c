#include <stdio.h>
#include <signal.h>

#include "bsd.h"

int s, child, i, j, bold = 0, frames, backendpid;
FILE *fp, *outp, *inp;
char buff[1024],filein[100], fileout[100], host[100], info[100];

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
  fclose(inp);
  unlink(filein);
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
  sprintf(filein,"%s.in",argv[1]);
  sprintf(fileout,"%s.out",argv[1]);
  sprintf(info,"%s.info",argv[1]);
  fp = fopen(info,"r");
  fscanf(fp,"%s",host);
  fscanf(fp,"%d",&frames);
  fscanf(fp,"%d",&backendpid);

  s = bsd_open("poledra.coyote.org", 4201);
  if (s < 0) shutd("Could not open BSD Socket");

  if ( (child = fork()) == -1 ) shutd("Can't fork subprocess!");

  if (!child) {
    signal(SIGTERM,(void (*)())clientdied);
    signal(SIGPIPE,(void (*)())clientdied);
    if (frames) outp = stdout;
    else outp = fopen(fileout, "w");
    while (1) {
      usleep(100);
      i = recv(s,buff,1024,0);
      if (i > 0) {
        for (j = 0; j < i; j++)
        if (buff[j] == '\n') {
          fprintf(outp,"<BR>");
          fflush(outp);
        }
        else if (buff[j] == '<') fprintf(outp,"&lt;");
        else if (buff[j] == '>') fprintf(outp,"&gt;");
        else if ((buff[j] == 0x1b) && (buff[j+1] == '[')) /* ANSI */ {
          j += 2;
          if ( (buff[j] == '0') && (bold)) {
            fprintf(outp,"</B>");
            bold = 0;
          } else if ( (buff[j] == '1') && !(bold)) {
            fprintf(outp,"<B>");
            bold = 1;
          }
          j++;
        } else fprintf(outp,"%c",buff[j]);
      } else if ( errno != EWOULDBLOCK )
          shutd(NULL);
    }
  } else {
    signal(SIGTERM,(void (*)())parentdied);
    while (1)
      if ( (inp = fopen(filein, "r")) != NULL ) {
         while ( (i = fread(buff,1,1024,inp)) != 0)
            send(s,buff,i,0);
         close(inp);
         unlink(filein);
      }
   }
}
