#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>


#include "generic.h"
#include "global.h"

#ifdef NCURSES
#include <ncurses.h>
#endif







/*

Fast MD5 generation core


*/



/* passwords <= 12 bytes (begin) */
/* 
   OK 
*/


int crack4_begin_core1(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  register char *a,*b,*c,*d,*e,*f,*g,*h;
  char *copy;
  register unsigned int MAX=(unsigned int) alfa+strlen(alfa+1)+1;
  register unsigned int MIN=(unsigned int) alfa+1; 
  unsigned char i,j; 
  unsigned int offset=0;
  char *mov;
  char digest[16];
  struct timeval *tp;
  unsigned int size=12;
  register unsigned int len_begin=0;
  unsigned int flag1, flag2, flag3, flag4;
  


 
  tp=(struct timeval *)malloc(sizeof(struct timeval)); 
  if (!tp)
   {
     mdmesg(7, NULL);
     doexit();
   }



  bzero(digest, 16);
  mov=digest;
  copy=input;
  strncpy(target, input, 32);
  
  a=b=c=d=e=f=g=(char *)alfa;
  h=(char *) MIN;
  


  up2low(input);
  ascii2bin(copy, conv, mov);
  Decode(digest2, mov, 16);  

  test=(char *)malloc(size);
  if (!test)
    {
      mdmesg(7, NULL);
      doexit();
    }
  total=test;

  bzero(test, size);


  if (resume[0])
    {     
      offset=len_begin=strlen(begin);
      len=strlen(resume)-len_begin;
      
      for (i=0; i<len; i++)
	for (j=1;j<=strlen(alfa+1);j++)
	  if (resume[len_begin+i]==alfa[j])
	    { 
	      if (!i)   h=alfa+j;
	      if (i==1) g=alfa+j;
	      if (i==2) f=alfa+j;
	      if (i==3) e=alfa+j;
	      if (i==4) d=alfa+j;
	      if (i==5) c=alfa+j;
	      if (i==6) b=alfa+j;
	      if (i==7) a=alfa+j;
            }
      len+=offset;
      strncpy(test, resume, len);
      test=test+len_begin;
    }
  else
    {      
      offset=len_begin=strlen(begin);
      strncpy(test, begin, len_begin);
      test=test+len_begin;

    if (minimal)
	{
	  for (i=0; i<8; i++)
	    {
	     
	      switch(minimal-i+95)
		{
		case 'a':
		  g++;
		  *(test+1)=*g;
		  break;
		  
		case 'b':
		  f++;
		  *(test+2)=*f;
		  break;
		  
		case 'c':
		  e++;
		  *(test+3)=*e;
		  break;
		  
		case 'd':
		  d++;
		  *(test+4)=*d;
		  break;
		  
		case 'e':
		  c++;
		  *(test+5)=*c;
		  break;
		  
		case 'f':
		  b++;
		  *(test+6)=*b;
		  break;
		  
		case 'g':
		  a++;
		  *(test+7)=*a;
		  break;
		  
		}
	    }
	  len=minimal;
	}
      else
	len=1;  

      len += offset;
      *test=*h;
    }


  
  flag2=flag3=flag4=0;
 
  if (len_begin>2)flag2=1;
  if (len_begin>1) flag3=1;
  if (len_begin) flag4=1;
  
   
  tail=(unsigned int) len << 3;
  total[len]=0x80;
 
  printw("\nPassword size: %u \n", len);
  
  
#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif

#ifdef ISBIG_ENDIAN
  Decode(x1, total, 12);
#else
  x1=(unsigned int *)total;
#endif
  
 

  signal(SIGINT, handle);
  if (benchmode)
    {
      alarm(duration);
      signal(SIGALRM, handle);
    }
  
  
  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;
  

  goto firsttime;
  
  for(;a<(char *)MAX;a++)
    {
      *(test+7)=*a;
      for(;b<(char *)MAX;b++)
	{
	  *(test+6)=*b;
	  for(;c<(char *)MAX;c++)
	    {
	      *(test+5)=*c;
	      for(;d<(char *)MAX;d++)
		{
		  *(test+4)=*d;
		  for(;e<(char *)MAX;e++)
		    {
		      *(test+3)=*e;
		      for(;f<(char *)MAX;f++)
			{
			  *(test+2)=*f;
			  for(;g<(char *)MAX;g++)
			    {
			      *(test+1)=*g;			   
			      for(;h<(char *)(MAX);h++)
				{
firsttime:	       		  *test=*h;				  
      				  count++;	  				  
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 12);
#endif

				  
                                   
				  if (val=core41b())
				    {
				      if (!stats(total,len))
					mdmesg(8, NULL); 
				      if (!all)
					return(1);	
				      total[len]=0x80;
				    } 			      
				  
				}
                              h=(char *)MIN;
			      
			      
			      if (len<2+offset) 
				{
				  len++;
				  total[len]=0x80;
				  tail=(unsigned int) len << 3;
				 				  
				  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
				  refresh();
#else
				  fflush(stdout);
#endif 
				} 
			    } 
			  g=(char *)MIN;
			  
			  
			  if (len<3+offset) 
			    {
			      len++;
			      tail=(unsigned int) len << 3;
			      total[len]=0x80;
			      fast=0;
			      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			      refresh();
#else		      
			      fflush(stdout);
#endif	
			    }
			}	      
		      f=(char *)MIN;
		      
		      
		      if (len<4+offset) 
			{
			  len++;
			  tail=(unsigned int) len << 3;
			  total[len]=0x80;
			  
			  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			  refresh();
#else		 
			  fflush(stdout);
#endif	
			} 		      
		    }
		  e=(char *)MIN;
		 
		  
		  if (len<5+offset) 
		    {
		      len++;
		      tail=(unsigned int) len << 3;
		      total[len]=0x80;
		      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		      refresh();
#else	      
		      fflush(stdout);
#endif	
		    }
		  
		}

              d=(char *)MIN;
	      
	      if (len<6+offset) 
		{
		  len++;
		  tail=(unsigned int) len << 3;
		  total[len]=0x80;
		  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		  refresh();
#else	
		  fflush(stdout);
#endif	
		}
	        
	    }
	  
          c=(char *)MIN;
	  
	  if (len<7+offset) 
	    {
	      len++;
	      tail=(unsigned int) len << 3;
	      total[len]=0x80;
	      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	      refresh();
#else	     
	      fflush(stdout);
#endif	
	    }
	 
	}
      
      b=(char *)MIN;
      
      if (len<8+offset) 
	{
	  len++;
	  tail=(unsigned int) len << 3;
	  total[len]=0x80;
	  
	  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	  refresh();
#else
	  fflush(stdout);
#endif
	}
      
    }
  return(0);
}















/* passwords <= 12 bytes (end/begin) */
/* OK */


int crack4_begin_end_core1(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  register char *a,*b,*c,*d,*e,*f,*g,*h;
  char *copy;
  unsigned int MAX=(unsigned int) alfa+strlen(alfa+1)+1;
  unsigned int MIN=(unsigned int) alfa+1; 
  unsigned char i,j; 
  unsigned int offset=0;
  char *mov2;
  char digest[16];
  struct timeval *tp;
  unsigned int size=12;
  register unsigned int len_begin=0, len_end=0;


  tp=(struct timeval *)malloc(sizeof(struct timeval)); 
  if (!tp)
   {
     mdmesg(7, NULL);
     exit(0);
   }
  bzero(digest, 16);
  mov2=digest;
  copy=input;
  strncpy(target, input, 32);
  
    a=b=c=d=e=f=g=(char *)alfa;
    h=(char *) MIN;

  up2low(input);
  ascii2bin(copy, conv, mov2);
  Decode(digest2, mov2, 16);  

  test=(char *)malloc(size);
  if (!test)
    {
      mdmesg(7, NULL);
      doexit();
    }
  
  bzero(test, size);
  


  if (resume[0])
    {

     offset=len_end=strlen(end);
     offset+=len_begin=strlen(begin);
   
     len=strlen(resume)-offset;

     total=test;
     test=test+len_begin;   

     for (i=0; i<len; i++)
       for (j=1;j<=strlen(alfa+1);j++)
         if (resume[len_begin+i]==alfa[j])
            { 
             if (!i)   h=alfa+j;
             if (i==1) g=alfa+j;
             if (i==2) f=alfa+j;
             if (i==3) e=alfa+j;
             if (i==4) d=alfa+j;
             if (i==5) c=alfa+j;
             if (i==6) b=alfa+j;
             if (i==7) a=alfa+j;
            }
     mov2=test+len_begin+len;
     len+=offset;
     strncpy(test, resume, len);

    }
  else
    {
      offset=len_end=strlen(end); 
      offset+=len_begin=strlen(begin);
      memcpy(test, begin, len_begin);

      total=test;
      test=test+len_begin;
     
      if (minimal)
	{
	  for (i=0; i<8; i++)
	    {
	     
	      switch(minimal-i+95)
		{
		case 'a':
		  g++;
		  *(test+1)=*g;
		  break;
		  
		case 'b':
		  f++;
		  *(test+2)=*f;
		  break;
		  
		case 'c':
		  e++;
		  *(test+3)=*e;
		  break;
		  
		case 'd':
		  d++;
		  *(test+4)=*d;
		  break;
		  
		case 'e':
		  c++;
		  *(test+5)=*c;
		  break;
		  
		case 'f':
		  b++;
		  *(test+6)=*b;
		  break;
		  
		case 'g':
		  a++;
		  *(test+7)=*a;
		  break;
		  
		}
	    }
	  len=minimal;
	}
      else
	len=1;      
    
      
      mov2=test+len;
      memcpy(mov2, end, len_end);
      len += offset;
    }




  total[len]=0x80;
  tail=(unsigned int) len << 3;


#ifdef ISBIG_ENDIAN
  Decode(x1, total, 12);
#else
  x1=(unsigned int *)total;
#endif


   



  signal(SIGINT, handle);
  if (benchmode)
    {
     alarm(duration);
     signal(SIGALRM, handle);
    }


  tail=(unsigned int) len << 3;
  printw("\nPassword size: %u \n", len);

#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif


  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;

  goto firsttime;

  for(;a<(char *)MAX;a++)
    {
       *(test+7)=*a;
      for(;b<(char *)MAX;b++)
	{
	  *(test+6)=*b;
	  for(;c<(char *)MAX;c++)
	    {
	      *(test+5)=*c;
	      for(;d<(char *)MAX;d++)
		{
		  *(test+4)=*d;
		  for(;e<(char *)MAX;e++)
		    {
		      *(test+3)=*e;
		      for(;f<(char *)MAX;f++)
			{
			  *(test+2)=*f;
			  for(;g<(char *)MAX;g++)
			    {
			      *(test+1)=*g;
			      for(;h<(char *)MAX;h++)
				{

firsttime:	      		  *test=*h;
				  count++;
				 

#ifdef ISBIG_ENDIAN
                                Decode(x1, total, 12);
#endif			

				  if (val=core41b())
				   {
				    if (!stats(total, len))
				      mdmesg(8, NULL);
				              
                                      if (!all)
				         return(1);
				      total[len]=0x80;
				   }
				  
			       

				}
			      
                              h=(char *)MIN;
			      
			      if (len<2+offset) 
				{
				  
				  len++;
				  total[len]=0x80;
				  mov2++;
				  memcpy(mov2, end, len_end);
				  tail=(unsigned int) len << 3;
				  
				  
				  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
				  refresh();
#endif
				  fflush(stdout);
				}
			    

			    }
			  
                           g=(char *)MIN;
			   
			   if (len<3+offset) 
			     {
			      
			      len++;
			      total[len]=0x80;
			      mov2++;
			      memcpy(mov2, end, len_end);
			      tail=(unsigned int) len << 3;
  
			     
			      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			      refresh();
#endif
			      fflush(stdout);
			     }
			  
			}
		       
                       f=(char *)MIN;
		      
		       if (len<4+offset) 
			 {
			 
			  len++;
			  total[len]=0x80;
			  mov2++;
			  memcpy(mov2, end, len_end);
			  tail=(unsigned int) len << 3;
		       
      			  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			  refresh();
#endif
			  fflush(stdout);
			 }
		      
		    }
		   
                   e=(char *)MIN;
		   
		   if (len<5+offset) 
		     {
		      len++;
		      total[len]=0x80;
		      mov2++;
		      memcpy(mov2, end, len_end);
		      tail=(unsigned int) len << 3;
		      
		      
		      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		      refresh();
#endif
		      fflush(stdout);
		     }
		  
		}
	     
              d=(char *)MIN;
      
	      if (len<6+offset) 
		{
		 len++;
		 total[len]=0x80;
		 mov2++;
		 memcpy(mov2, end, len_end);
		 tail=(unsigned int) len << 3;
		 
		 
		 printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		 refresh();
#endif
		 fflush(stdout);
		}
	     
	    }
	  
          c=(char *)MIN;
	
          if (len<7+offset) 
	    {
	     len++;
	     total[len]=0x80;
	     mov2++;
	     memcpy(mov2, end, len_end);
	     tail=(unsigned int) len << 3;
	    
	    
	     printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	     refresh();
#endif
	     fflush(stdout);
	    }

	  
	}
     
      b=(char *)MIN;
     
      if (len<8+offset) 
	{
	  len++;
	  total[len]=0x80;
	  mov2++;
	  memcpy(mov2, end, len_end);
	  tail=(unsigned int) len << 3;
	 
	 
	  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	  refresh();
#endif
	  fflush(stdout);
	}
      
    }

  return(0);
}






 int core41b(void)
{
  register unsigned int a;
  register unsigned int	b;
  register unsigned int	c;
  register unsigned int	d;



   

  b = 0xefcdab89;
  c = 0x98badcfe;
  d = 0x10325476; 
  a = 0x67452301;  


  NFF (a, b, c, d, x1[0], S11, SS11);       /* 1  */
  NFF (d, a, b, c, x1[1], S12, SS12);       /* 2  */
  NFF (c, d, a, b, x1[2], S13, SS13);       /* 3  */
  NFF0 (b, c, d, a, S14, SS14);             /* 4  */
  NFF0 (a, b, c, d, S11, SS11);             /* 5  */
  NFF0 (d, a, b, c, S12, SS12);             /* 6  */
  NFF0 (c, d, a, b, S13, SS13);             /* 7  */
  NFF0 (b, c, d, a, S14, SS14);             /* 8  */
  NFF0 (a, b, c, d, S11, SS11);             /* 9  */
  NFF0 (d, a, b, c, S12, SS12);             /* 10 */
  NFF0 (c, d, a, b, S13, SS13);             /* 11 */
  NFF0 (b, c, d, a, S14, SS14);             /* 12 */
  NFF0 (a, b, c, d, S11, SS11);             /* 13 */
  NFF0 (d, a, b, c, S12, SS12);             /* 14 */
  NFF (c, d, a, b, tail, S13, SS13);        /* 15 */
  NFF0 (b, c, d, a, S14, SS14);             /* 16 */
  


  /*

    Round 2

  */
  
  NGG (a, b, c, d, x1[0], S21, SS21);       /* 17 */
  NGG0 (d, a, b, c,  S22, SS22);            /* 18 */
  NGG0 (c, d, a, b, S23, SS23);             /* 19 */
  NGG0 (b, c, d, a, S24, SS24);             /* 20 */
  NGG (a, b, c, d, x1[1],S21, SS21);        /* 21 */
  NGG0 (d, a, b, c, S22, SS22);             /* 22 */
  NGG0 (c, d, a, b, S23, SS23);             /* 23 */
  NGG0 (b, c, d, a, S24, SS24);             /* 24 */
  NGG (a, b, c, d, x1[2],S21, SS21);        /* 25 */
  NGG0 (d, a, b, c,S22, SS22);              /* 26 */
  NGG0 (c, d, a, b, S23, SS23);             /* 27 */
  NGG (b, c, d, a,tail,  S24, SS24);        /* 28 */
  NGG0 (a, b, c, d, S21, SS21);             /* 29 */
  NGG0 (d, a, b, c,S22, SS22);              /* 30 */
  NGG0 (c, d, a, b, S23, SS23);             /* 31 */
  NGG0 (b, c, d, a, S24, SS24);             /* 32 */
  
 

  /*

    Round 3

  */

  NHH (a, b, c, d, x1[0], S31, SS31);       /* 33 */
  NHH0 (d, a, b, c, S32, SS32);             /* 34 */
  NHH0 (c, d, a, b, S33, SS33);             /* 35 */
  NHH0 (b, c, d, a, S34, SS34);             /* 36 */
  NHH (a, b, c, d, x1[2], S31, SS31);       /* 37 */
  NHH0 (d, a, b, c, S32, SS32);             /* 38 */
  NHH0 (c, d, a, b, S33, SS33);             /* 39 */
  NHH (b, c, d, a, tail, S34, SS34);        /* 40 */
  NHH (a, b, c, d, x1[1],S31, SS31);        /* 41 */
  NHH0 (d, a, b, c, S32, SS32);             /* 42 */
  NHH0 (c, d, a, b, S33, SS33);             /* 43 */
  NHH0 (b, c, d, a, S34, SS34);             /* 44 */
  NHH0 (a, b, c, d, S31, SS31);             /* 45 */
  NHH0 (d, a, b, c, S32, SS32);             /* 46 */
  NHH0 (c, d, a, b, S33, SS33);             /* 47 */ 
  NHH0 (b, c, d, a, S34, SS34);             /* 48 */ 
 

  a  += 0x67452301;
  b  += 0xefcdab89;
  c  += 0x98badcfe;
  d  += 0x10325476;
  


 if ((digest2[0]== a) && (digest2[1] == b) && (digest2[2] == c) && (digest2[3] == d))
   return 1; 
 
 
 return 0;
}



















































