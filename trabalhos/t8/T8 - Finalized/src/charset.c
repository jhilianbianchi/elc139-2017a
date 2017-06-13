
/*

 charset.c

 Custom charsets sanitization

*/



#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef NCURSES
#include <ncurses.h>
#endif


#ifndef NCURSES
#define printw printf
#endif

int charset_sort(charset)
     char *charset;
{
  register int i,j,flag;
  unsigned int length;
  char *buf;

  mdmesg(27, NULL);

  length=strlen(charset);
  buf=(char *)malloc(length+1);
  if (!buf)
    {
      mdmesg(7, NULL);
      exit(0);
    }
  bzero(buf, length);
  for (i=0;i<length;i++)
    {
      flag=0;
      for (j=0;j<strlen(buf);j++)
	{
	  if (*(charset+i)==*(buf+j)) 
	    {
	      flag=1;
	      continue;
	    }
	}
      if (!flag)
	*(buf+strlen(buf))=*(charset+i);
     
    }

  printw("done");

#ifdef NCURSES
  refresh();
#endif
  
  if (strcmp(charset, buf))
    {
      strcpy(charset, buf);
      mdmesg(28, NULL);
      return(1);
    }

  strcpy(charset, buf);

 
  return(0);
}













