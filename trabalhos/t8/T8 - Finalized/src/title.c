/*

title.c 

 */




#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "./global.h"
#ifdef NCURSES
#include <ncurses.h>
#include <stdlib.h>
#endif



#ifndef NCURSES
#define printw printf
#endif

#define XVIRTU 70
#define YVIRTU 8
#define XSCREEN 60
#define YSCREEN 6
#define Y 4
#define X 51

void clear_logo(unsigned int, unsigned int);
void print_logo(unsigned int, unsigned int, unsigned int);
void blink_logo(unsigned int, unsigned int, unsigned int);
void blink2_logo(unsigned int, unsigned int, unsigned int);
void shadow_logo(unsigned int, unsigned int, unsigned int);
void flash_screen(unsigned int, unsigned int, unsigned int);
void flash_screen2(unsigned int, unsigned int, unsigned int);




char  logo[Y][X]= {  "~    ~  ~~~\\   ~~\\   ~~~\\  ~~~   ~~\\  ~   ~        ",\
	             "    /|      |  |       )    __|  |      /          ",\
                     "| || |   |  |  |    |   / |   |  |    | \\          ",\
                     "|    |  ___/   __/  |    \\|   |  __/  |  \\   1.2 ",\
};



char copy[Y][X];


void logow()
   
{
  register unsigned int i,j,k;



#ifdef NCURSES
  
  mvwprintw(stdscr, 1, 0, " ");
  clrtoeol();
  mvwprintw(stdscr, 23, 0, " ");
  attrset(COLOR_PAIR(2));
  mdmesg(30, NULL);
  attrset(COLOR_PAIR(2)|A_BLINK);
  
  mdmesg(35, NULL);

  for(;;)
    {
    
      flash_screen(4, 1, 3);
      print_logo(6, 1, 1);
      blink_logo(6, 1, 3);
      blink2_logo(6, 1, 3);
      for (k=0;k<XVIRTU+2;k+=1)
	{
	  usleep(20000);
	  print_logo((6+k-1), 1, 0);
	  print_logo((6+k), 1, 1);
	  refresh();
	}
      blink_logo(6+k-1, 1, 3);
      blink2_logo(6+k-1, 1, 3);
      if (getch()!=ERR) doexit2();
      sleep(1);
      print_logo((6+k-1), 1, 0);
      for (k=0;k<XVIRTU+2;k+=2)
	{
	  usleep(20000);
	  print_logo((6+k-2), 1, 0);
	  print_logo((6+k), 1, 1);
	  refresh();
	}
      sleep(1);
      shadow_logo( (6+k-2), 1, 2);
  
      
      flash_screen2(4, 1, 3);
      
      slogan_screen2("       Bruteforce your hashes      ", 16, 2, 3);
      sleep(2);
      clear_line(4, 2);
      usleep(100000);
      slogan_screen("             Homepages             ", 16, 2, 3);
      usleep(100000);   
      slogan_screen("    >>  http://mdcrack.df.ru  <<    ", 16, 4, 3);
      usleep(100000);   
      slogan_screen(">>  http://mdcrack.multimania.com  << ", 16, 5, 3);

      sleep(5);
      clear_line(4, 2);
      clear_line(4, 4);
      clear_line(4, 5);
      slogan_screen2("  Send your benchmarks & questions  ", 16, 2, 3);
      slogan_screen2("  to ", 29, 3, 3);
      slogan_screen2("  c3rb3r@hotmail.com ", 22, 4, 3);
      sleep(2);
    }

 

#else

  printf("\n\n");

  for(i=0;i<Y;i++)
    {
      for(j=0;j<X;j++)
	printf("%c", logo[i][j]);
      printf("\n");
    }
  printf("\n");

#endif
  
     
#ifdef NCURSES

 attrset(COLOR_PAIR(1));   

#endif

}



#ifdef NCURSES


clear_line(x, y)
     unsigned int x;
     unsigned int y;
{
  unsigned int i;

  attrset(COLOR_PAIR(5));
  for (i=0; i<XSCREEN; i++)  
    mvwprintw(stdscr, y, x+i, SYMBOL);
  refresh();
}  



slogan_screen(comment, x, y, sync)
     unsigned char *comment;
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  attrset(COLOR_PAIR(2));
  mvwprintw(stdscr, y, x, comment);
  refresh();
 
  usleep(sync*10000);
  attrset(COLOR_PAIR(2)|A_BOLD);
  mvwprintw(stdscr, y, x, comment);
  refresh();
  
  usleep(sync*10000);
  attrset(COLOR_PAIR(6)|A_BOLD);
  mvwprintw(stdscr, y,x, comment);
  refresh();

  usleep(sync*10000);
  attrset(COLOR_PAIR(6));
  mvwprintw(stdscr, y,x, comment);
  refresh();
 
  if (getch()!=ERR) doexit2();
  usleep(sync*10000);
}  




slogan_screen2(comment, x, y, sync)
     unsigned char *comment;
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  register unsigned int i;
  
  
  for (i=0; i<strlen(comment); i++)
    {
      attrset(COLOR_PAIR(6)|A_BOLD);
      mvwprintw(stdscr, y, x+i, "%c", comment[i]);
      refresh();
   
      usleep(sync*10000);
      attrset(COLOR_PAIR(6));
      mvwprintw(stdscr, y, x+i, "%c", comment[i]);
      refresh();

      if (getch()!=ERR) doexit2();
      usleep(sync*10000);
    }
     
  usleep(sync*10000);
  attrset(COLOR_PAIR(2)|A_BOLD);
  mvwprintw(stdscr, y,x, comment);
  refresh();
 
  usleep(sync*10000);
  attrset(COLOR_PAIR(6)|A_BOLD);
  mvwprintw(stdscr, y,x, comment);
  refresh();
 
  usleep(sync*10000);
  attrset(COLOR_PAIR(6)); 
  mvwprintw(stdscr, y,x, comment);
  refresh();
  if (getch()!=ERR) doexit2();
  usleep(sync*10000);
}  




void clear_logo(x, y)
     register unsigned int x;
     register unsigned int y;
{
  register unsigned int i, j;
  
  attrset(COLOR_PAIR(5));
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();
}




void flash_screen(x, y, sync)
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  register unsigned int i, j;
  
  attrset(COLOR_PAIR(6)|A_BOLD);
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();
  
  usleep(sync*10000);
 attrset(COLOR_PAIR(6));
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();
  
  usleep(sync*10000);
  attrset(COLOR_PAIR(5));
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
        mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();

  if (getch()!=ERR) doexit2();
}



void flash_screen2(x, y, sync)
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  register unsigned int i, j;
  
  attrset(COLOR_PAIR(2)|A_BOLD);
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();
 
  usleep(sync*10000);
  attrset(COLOR_PAIR(6)|A_BOLD);
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();

  usleep(sync*10000);
  attrset(COLOR_PAIR(6));
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();

  usleep(sync*10000);
  attrset(COLOR_PAIR(5));
  for (i=0;i<YSCREEN;i++)
    for (j=0;j<XSCREEN;j++)
      mvwprintw(stdscr, y+i, x+j, SYMBOL);
  refresh();
  if (getch()!=ERR) doexit2();
  usleep(sync*10000);


}





void print_logo(x, y, color)
  unsigned int x;
  unsigned int y;
  unsigned int color;
 {
   register unsigned int i, j;
   register unsigned int e;

   if (color)
     {
       if (color==1)
	 attrset(COLOR_PAIR(6));
       else if (color==2)
	  attrset(COLOR_PAIR(6)|A_BOLD);
       else if (color==3)
	 attrset(COLOR_PAIR(2)|A_BOLD);

       for(i=0;i<Y;i++)
	 for(j=0;j<X;j++)
	   {
	     e=(x+j)%XVIRTU;
	     if (e<XSCREEN)
	       {
		 if (logo[i][j]!=' ')
		   {
		     if ((e>10) && ((e+4)<42))
		       attrset(COLOR_PAIR(6)|A_BOLD);
		     else
		       attrset(COLOR_PAIR(6));
		     mvwprintw(stdscr, y+i, e+4, "%c", logo[i][j]);
		   }
	       }	  
	   }
     }
   
   else
     {
       attrset(COLOR_PAIR(5)); 
       for(i=0;i<Y;i++)
	 for(j=0;j<X;j++)	   
	   {  
	     e=(x+j)%XVIRTU;
	     if (e<XSCREEN)
	       {
		 if (logo[i][j]!=' ')
		   mvwprintw(stdscr, y+i, e+4, SYMBOL);
	       }
	   }	   
     }
 }


       
   

void blink_logo(x, y, sync)
  unsigned int x;
  unsigned int y;
  unsigned int sync;
{
   register unsigned int i, j;

   print_logo(x, y, 0);
   refresh();
   usleep(sync*10000);
   print_logo(x, y, 1);
   refresh();
   if (getch()!=ERR) doexit2();
   usleep(sync*10000);
   
}



void blink2_logo(x,y,sync)
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  print_logo(x, y, 3);
  refresh();
  usleep(sync*10000);
  print_logo(x, y, 2);
  refresh();
  usleep(sync*10000);
  print_logo(x, y, 1);
  refresh();
  if (getch()!=ERR) doexit2();
  usleep(sync*10000);
}




void shadow_logo(x,y,sync)
     unsigned int x;
     unsigned int y;
     unsigned int sync;
{
  register int flag=0,i,j,e;
  
  for(i=0;i<Y;i++)
    for (j=0;j<X;j++)
      copy[i][j]=logo[i][j];

  while(!flag)
    {
      flag=1;
      if (getch()!=ERR) doexit2();
      for(i=0;i<Y;i++)
	for(j=0;j<X;j++)
	  {

	    if (copy[i][j]!=' ')
	      {
		flag=0;
		
		if ((int) (10*(float)rand()/(RAND_MAX+1.0) <= 4))  
		  {	
		    e=(x+j)%XVIRTU;
		    
		    attrset(COLOR_PAIR(6)|A_BOLD);
		    mvwprintw(stdscr, (y+i), e+4, "%c", copy[i][j]);
		    refresh();
		    usleep(sync*10000);
		 
		    attrset(COLOR_PAIR(6));
		    mvwprintw(stdscr, (y+i), e+4, "%c", copy[i][j]);
		    refresh();
		    usleep(sync*10000);

		    attrset(COLOR_PAIR(5));
		    mvwprintw(stdscr, (y+i), e+4, "%c", logo[i][j]);
		    refresh();
		    usleep(sync*10000);
		    copy[i][j]=' ';
		    
		  }	
	      }
	  }
      refresh();
    }
  
}


#endif












