#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cgi.h"

int get_var(char *source,char *dest,char *var)
{
 int c = 0, size = strlen(var);
 char h, i = '\0', *p_copy = (char *)strstr(source,var);

 if (p_copy == NULL)
   return(-1);
 while (i != '&')
 {
   i = *(p_copy+size+c+1);
   switch(i) {
     case '+':
        *(dest+c) = ' ';
        c++;
        break;

     case '&':
        break;

     case '%':
        *(dest+c) = (char)decode_hex(p_copy+size+c+1);
        c++;
        p_copy += 2;
        break;
     default:
        *(dest+c) = i;
        c++;
        break;
   }
 }
 *(dest+c) = '\0';
 return (c-1);
}

int decode_hex(char *hex)
{
 char string[3];
 int i;
 long l;

 if ((sscanf(hex, "%%%c%c", &string[0], &string[1]))==0)
   return((int)'+');
 string[2] = 0;
 i = strtol(string, NULL, 16);
 return(i);
}

