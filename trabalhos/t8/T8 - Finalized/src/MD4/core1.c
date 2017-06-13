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

Fast MD4 generation core


*/


int md4_reverse(unsigned int *hash)
{

  fasta=hash[0];
  fastb=hash[1];
  fastc=hash[2];
  fastd=hash[3];

  fasta  -= 0x67452301;
  fastb  -= 0xefcdab89;
  fastc  -= 0x98badcfe;
  fastd  -= 0x10325476;

  RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 48 */
  RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 47 */ 
  RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 46 */
  RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 45 */
  RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 44 */
  RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 43 */
  RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 42 */
  RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 41 */

  working[0]=fasta;
  working[1]=fastb;
  working[2]=fastc;
  working[3]=fastd; 

}



/* passwords <= 12 bytes (nothing) */
/* 
   OK 
*/


int crack4_core1(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  register char *a,*b,*c,*d,*e,*f,*g,*h;
  char *copy;
  register unsigned int MAX=(unsigned int) alfa+strlen(alfa+1)+1;
  register unsigned int MIN=(unsigned int) alfa+1; 
  unsigned char i,j; 
  char *mov;
  char digest[16];
  struct timeval *tp;
  unsigned int size=12;
  
  


 
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
    h=(char *)MIN;


  test=(char *)malloc(size);
  if (!test)
    {
      mdmesg(7, NULL);
      doexit();
    }
   bzero(test, size);

 
  if (resume[0])
    {     
      len=strlen(resume);
      
      for (i=0; i<len; i++)
	for (j=1;j<=strlen(alfa+1);j++)
	  if (resume[i]==alfa[j])
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
      strncpy(test, resume, len);
    }
  else
    {
      *test=*h;

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
      
    }
  
 
 
 
  up2low(input);
  ascii2bin(copy, conv, mov);
  Decode(digest2, mov, 16);  
  
  md4_reverse(digest2);  
  fast=0;
 
  total=test;

  total[len]=0x80;
  tail=(unsigned int) len << 3;
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
			      for(;h<(char *)(MAX);h+=2)
				{
firsttime:	       		  *test=*h;				  
      				  count+=2;	  				  
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 12);
#endif
				  diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));
				  
				  
                                   
				  if (val=core41())
				    {
				      if (!stats(total,len))
					mdmesg(8, NULL); 
				      if (!all)
					return(1);	
				      total[len]=0x80;
				    } 			      
		                 		  
				}
                              h=(char *)MIN;
			   
			      
			      if (len<2) 
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
			  g=(char *)MIN;
		      
			  
			  if (len<3) 
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
		  
		      
		      if (len<4) 
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
		  e=(char *)MIN;
		  fast=0;
		  
		  if (len<5) 
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
	      
	      if (len<6) 
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
	  
	  if (len<7) 
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
      
      if (len<8) 
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













/* passwords <= 12 bytes (end) */
/* OK */


int crack4_end_core1(input, resume)
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
  register unsigned int len_end=0;


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
  h=(char *)MIN;



  test=(char *)malloc(size);
  if (!test)
    {
      mdmesg(7, NULL);
      doexit();
    }
  bzero(test, size);
  
  up2low(input);
  ascii2bin(copy, conv, mov2);
  Decode(digest2, mov2, 16); 
  md4_reverse(digest2);

  fast=0;
  
  if (resume[0])
    {
      
      offset=len_end=strlen(end);  
      len=strlen(resume)-offset;
      
      
      for (i=0; i<len; i++)
	for (j=1;j<=strlen(alfa+1);j++)
	  if (resume[i]==alfa[j])
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
      mov2=test+len;
      len+=offset;
      memcpy(test, resume, len);
    }
  else
    { 
      offset=len_end=strlen(end); 
      *test=*h;
      
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
  
    
  total=test;
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
			      for(;h<(char *)MAX;h+=2)
				{
				  
firsttime:		       	*test=*h;
				count+=2;
				diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));
				
#ifdef ISBIG_ENDIAN
				Decode(x1, total, 12);
#endif			
				
				if (val=core41())
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
				  fast=0;
				  len++;
				  total[len]=0x80;
				  mov2++;
				  memcpy(mov2, end, len_end);
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
			      fast=0;
			      len++;
			      total[len]=0x80;
			      mov2++;
			      memcpy(mov2, end, len_end);
			      tail=(unsigned int) len << 3;
			      
			      
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
			  fast=0;
			  len++;
			  total[len]=0x80;
			  mov2++;
			  memcpy(mov2, end, len_end);
			  tail=(unsigned int) len << 3;
			  
			  
			  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			  refresh();
#else
			  fflush(stdout);
#endif	
			}
		      
		    }
		  
		  e=(char *)MIN;
		  fast=0;
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
#else
		      fflush(stdout);
#endif	
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
#else
		  fflush(stdout);
#endif	
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
#else
	      fflush(stdout);
#endif	
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
#else
	  fflush(stdout);
#endif	
	}
      
    }
  
  return(0);
}






 int core41(void)
{
  register unsigned int a,a1;
  register unsigned int	b,b1;
  register unsigned int	c,c1;
  register unsigned int	d,d1;


 
  a = 0x67452301;
  a1 = 0x67452301;
  b = 0xefcdab89;
  b1 = 0xefcdab89;
  c = 0x98badcfe;
  c1 = 0x98badcfe;
  d = 0x10325476; 
  d1 = 0x10325476;

  NDNFF (a, b, c, d, x1[0], S11, SS11, a1, b, c, d);  /* 1  */
  DNFF (d, a, b, c, x1[1], S12, SS12, d1, a1, b, c);  /* 2  */
  DNFF (c, d, a, b, x1[2], S13, SS13, c1, d1, a1, b); /* 3  */
  DNFF0 (b, c, d, a, S14, SS14, b1, c1, d1, a1);      /* 4  */
  DNFF0 (a, b, c, d, S11, SS11, a1, b1, c1, d1);      /* 5  */
  DNFF0 (d, a, b, c, S12, SS12, d1, a1, b1, c1);      /* 6  */
  DNFF0 (c, d, a, b, S13, SS13, c1, d1, a1, b1);      /* 7  */
  DNFF0 (b, c, d, a, S14, SS14, b1, c1, d1, a1);      /* 8  */
  DNFF0 (a, b, c, d, S11, SS11, a1, b1, c1, d1);      /* 9  */
  DNFF0 (d, a, b, c, S12, SS12, d1, a1, b1, c1);      /* 10 */
  DNFF0 (c, d, a, b, S13, SS13, c1, d1, a1, b1);      /* 11 */
  DNFF0 (b, c, d, a, S14, SS14, b1, c1, d1, a1);      /* 12 */
  DNFF0 (a, b, c, d, S11, SS11, a1, b1, c1, d1);      /* 13 */
  DNFF0 (d, a, b, c, S12, SS12,d1, a1, b1, c1);       /* 14 */
  DNFF (c, d, a, b, tail, S13, SS13, c1, d1, a1, b1);      /* 15 */
  DNFF0 (b, c, d, a, S14, SS14, b1, c1, d1, a1);      /* 16 */
  


  /*

    Round 2

  */

  
  NDNGG (a, b, c, d, x1[0], S21, SS21, a1, b1, c1, d1); /* 17 */
  DNGG0 (d, a, b, c,  S22, SS22, d1, a1, b1, c1);       /* 18 */
  DNGG0 (c, d, a, b, S23, SS23, c1, d1, a1, b1);        /* 19 */
  DNGG0 (b, c, d, a, S24, SS24, b1, c1, d1, a1);        /* 20 */
  DNGG (a, b, c, d, x1[1], S21, SS21, a1, b1, c1, d1);  /* 21 */
  DNGG0 (d, a, b, c, S22, SS22,  d1, a1, b1, c1);       /* 22 */
  DNGG0 (c, d, a, b, S23, SS23, c1, d1, a1, b1);        /* 23 */
  DNGG0 (b, c, d, a, S24, SS24, b1, c1, d1, a1);        /* 24 */
  DNGG (a, b, c, d, x1[2], S21, SS21, a1, b1, c1, d1);  /* 25 */
  DNGG0 (d, a, b, c, S22, SS22, d1, a1, b1, c1);        /* 26 */
  DNGG0 (c, d, a, b, S23, SS23, c1, d1, a1, b1);        /* 27 */
  DNGG (b, c, d, a, tail, S24, SS24, b1, c1, d1, a1);   /* 28 */
  DNGG0 (a, b, c, d, S21, SS21, a1, b1, c1, d1);        /* 29 */

  /*

    Round 3

  */

  
  if (!fast)
    {
      fasta = working[0];
      fastb = working[1];
      fastc = working[2];
      fastd = working[3];
      
      fasta -= x1[1];
      RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 40 */
      fastb -= tail;
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 39 */
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 38 */
      RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 37 */
      fasta -= x1[2];
  
      RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 36 */ 
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 35 */ 
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 34 */ 

      RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 33 */
      
      fast=1;

    }
  
 
  if ((fasta != a+x1[0]) && (fasta != a1+x1[0]+diff)) return(0);

 
  DNGG0 (d, a, b, c, S22, SS22, d1, a1, b1, c1);        /* 30 */
  DNGG0 (c, d, a, b, S23, SS23, c1, d1, a1, b1);        /* 31 */
  DNGG0 (b, c, d, a, S24, SS24, b1, c1, d1, a1);        /* 32 */
 
 
 if ((fastb == b) && (fastc == c) && (fastd == d))
   return 1; 
 if ((fastb == b1) && (fastc == c1) && (fastd == d1))
   return 2;


 return 0;
}



















































