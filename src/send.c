#include <stdio.h>

#include "cgi.h"

int main(int argc, char **argv)
{
  int i;
  char data[1024], ref[100], inp[1024], fname[100];
  int lens;
  char *str_len = (char *)getenv("CONTENT_LENGTH");
  FILE *fp;

  printf("Content-type: text/html\n\n<HTML><BODY>\n");

  printf("<FORM ACTION=\"send.cgi?%s\" METHOD=\"POST\">\n",argv[1]);

  if (str_len != NULL) {
     lens=strtol(str_len,NULL,10);
     for(i=0;i<lens;i++)
        data[i] = getchar();
     data[++i] = '&';

     if ((lens = get_var(data,inp,"F1")) == -1) {
        printf("Error processing input data</BODY></HTML>");
        exit(0);
     }
     sprintf(fname, "/tmp/%s.in",argv[1]);

     if ( (fp = fopen(fname, "a")) == NULL ) {
        printf("Error writing to disc</BODY></HTML>");
        exit(0);
     }

     fprintf(fp,"%s\n",inp);
     fclose(fp);

  }

  printf("<INPUT TYPE=\"TEXT\" NAME=\"F1\" SIZE=80>\n");
  printf("</FORM>\n");
  printf("</BODY></HTML>\n");
  return 0;
}

