#include <stdio.h>

#include "cgi.h"

int main(int argc, char **argv)
{
  char *host = (char *)getenv("REMOTE_HOST");
  char *cont_len = (char *)getenv("CONTENT_LENGTH");
  char tmpfile[100], frames[10], data[1024],randname[100];
  FILE *fp;
  int lens,i, child;

  lens=strtol(cont_len,NULL,10);
  for(i=0;i<lens;i++)
     data[i] = getchar();
  data[++i] = '&';
  data[++i] = 0;

  get_var(data,frames,"FRAMES");

  strcpy(randname,tempnam(NULL,NULL));
  sprintf(tmpfile,"%s.info",randname);

  if (strcmp(frames,"000") == 0) {
    if ((child = fork()) == -1) {
       exit(0);
    }
    if (child == 0) /* child */ {
      if (execl("/home/www/mush","nph-backend",randname,NULL) == -1) {
        exit(0);
      }
    } else {
      fp = fopen(tmpfile,"w");

      fprintf(fp,"%s\n",host);
      fprintf(fp,"0\n");
      fprintf(fp,"%d\n",child);
      fclose(fp);
      printf("Location: http://www.coyote.org/mush/frontend.cgi?%s",randname);
      exit(0);
    }
  } else {
    fp = fopen(tmpfile,"w");

    fprintf(fp,"%s\n",host);
    fprintf(fp,"1\n");
    fprintf(fp,"0\n");
    fclose(fp);
    printf("Location: http://www.coyote.org/mush/frontend.cgi?%s",randname);
    exit(0);
  }
  return 0;
}
