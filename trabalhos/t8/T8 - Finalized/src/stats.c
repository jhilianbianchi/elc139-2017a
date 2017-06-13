

/*

stats.c

statistics output system

*/






#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include "global.h"
#ifdef NCURSES
#include <ncurses.h>
#endif

extern unsigned int all, val;
extern long elapsed_u, elapsed;
extern long start_u, start;
extern unsigned long count;
extern unsigned char *test;
extern unsigned int algo;

#ifndef NCURSES
#define printw printf
#endif

extern unsigned int unicode2ascii(char *, unsigned int);
extern signed int diff;




int stats(char *total, unsigned int len)
{
  struct timeval ft;
  float sub;
  unsigned int i;
  char *output;
  

  
  gettimeofday(&ft, NULL);
  elapsed=(ft.tv_sec)-start;
  elapsed_u=(ft.tv_usec)-start_u;

  signal(SIGINT, SIG_DFL);
  alarm(0);

  output=(char *)malloc((len+1)*sizeof(char));
  bzero(output, (len+1));
  memcpy(output, total, len);

  if (algo==2)
    len=unicode2ascii(output, len);
    

#ifdef NCURSES
  attrset(COLOR_PAIR(2));
#endif
  
  if (val==2) output[0]=output[0]+diff;



  
  if ((elapsed_u<10000) && (!elapsed))
    {
      printw("\n\n");
      for (i=0; i<40; i++)
	{

#ifdef NCURSES 
	  if (((i<14)||(i>25))&&(i!=11)&&(i!=28))
	    attrset(COLOR_PAIR(1));
	  else
	    attrset(COLOR_PAIR(1)|A_BOLD);
#endif
	  printw(SYMBOL);
	}
      printw("\n");
      
      printw("Collision found ! => ");  
      
#ifdef NCURSES
      refresh();
      attrset(COLOR_PAIR(2)|A_BOLD);
#endif

      printw("%s\n", output);
      mdmesg(12, NULL);
    } 
  else
    {
      if (elapsed_u < 0)
	{
	  elapsed_u=1000000+elapsed_u;
	  if (elapsed>0) elapsed--;
	}

#ifdef NCURSES
      attrset(COLOR_PAIR(2));
#endif
      sub=(float)elapsed+((float)elapsed_u/1000000 );
      
      printw("\n\n");
      for (i=0; i<40; i++)
	{
	  
#ifdef NCURSES 
	  if (((i<14)||(i>25))&&(i!=11)&&(i!=28))
	    attrset(COLOR_PAIR(1));
	  else
	    attrset(COLOR_PAIR(1)|A_BOLD);
#endif

	  printw(SYMBOL);
	}
      printw("\n");
      printw("Collision found ! => ");  
      
      
#ifdef NCURSES
      refresh();
      attrset(COLOR_PAIR(2)|A_BOLD);
#endif
      
      printw("%s\n", output);
      
#ifdef NCURSES
      refresh();
      attrset(COLOR_PAIR(2));
#endif
      
      printw("\n\nCollision(s) tested : %lu in %u second(s), %u millisec, %u microsec.\nAverage of %.1f hashes/sec.\n\n", count, elapsed, (elapsed_u/1000), (elapsed_u%1000), (float)((long)count/sub));
      
    }
  
#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif
  
  free(output);
  return(1);
}





















