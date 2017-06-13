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


int crack_begin_core1(input, resume)
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




  a=b=c=d=e=f=g=(char *)alfa;
  h=(char *)MIN;

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
	
      len+=offset;
    }


  
  flag2=flag3=flag4=0;
 
  if (len_begin>2)flag2=1;
  if (len_begin>1) flag3=1;
  if (len_begin) flag4=1;
  

  
  digest2[0] -= 0x67452301;
  digest2[1] -= 0xefcdab89;  
  digest2[2] -= 0x98badcfe;  
  digest2[3] -= 0x10325476;
  
  

  
   
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
  
  md5_reverse();

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

				  
                                   
				  if (val=core1b())
				    {
				      if (!stats(total,len))
					mdmesg(8, NULL); 
				      if (!all)
					return(1);	
				      total[len]=0x80;
				    } 			      
				  
				}
                              h=(char *)MIN;
			      if (flag2) fast=0;
			      
			      if (len<2+offset) 
				{
				  len++;
				  total[len]=0x80;
				  tail=(unsigned int) len << 3;
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
			  if (flag3) fast=0;
			  
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
		      if (flag4) fast=0;
		      
		      if (len<4+offset) 
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
		  if (flag2)
		      md5_reverse();   
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
	      if (flag3)
		md5_reverse();     
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
	  if (flag4)
	    md5_reverse();
	}
      
      b=(char *)MIN;
      
      if (len<8+offset) 
	{
	  len++;
	  tail=(unsigned int) len << 3;
	  total[len]=0x80;
	  md5_reverse();
	  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	  refresh();
#else
	  fflush(stdout);
#endif
	}
      if (flag4)
	md5_reverse();
    }
  return(0);
}















/* passwords <= 12 bytes (end/begin) */
/* OK */


int crack_begin_end_core1(input, resume)
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
     total=test;
     test=test+len_begin;

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
	len+=offset;
    }



  
  digest2[0] -= 0x67452301;
  digest2[1] -= 0xefcdab89;  
  digest2[2] -= 0x98badcfe;  
  digest2[3] -= 0x10325476;


 
  total[len]=0x80;
  tail=(unsigned int) len << 3;


#ifdef ISBIG_ENDIAN
  Decode(x1, total, 12);
#else
  x1=(unsigned int *)total;
#endif


  md5_reverse();			  



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

				  if (val=core1b())
				   {
				    if (!stats(total, len))
				      mdmesg(8, NULL);
				              
                                      if (!all)
				         return(1);
				      total[len]=0x80;
				   }
				  
			       

				}
			      
                              h=(char *)MIN;
			      if (len_begin>2) fast=0;
			      if (len<2+offset) 
				{
				  fast=0;
				  len++;
				  total[len]=0x80;
				  mov2++;
				  memcpy(mov2, end, len_end);
				  tail=(unsigned int) len << 3;
				  
				  md5_reverse();
				  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
				  refresh();
#endif
				  fflush(stdout);
				}
			    

			    }
			  
                           g=(char *)MIN;
			   if (len_begin>1) fast=0;
			   if (len<3+offset) 
			     {
			      fast=0;
			      len++;
			      total[len]=0x80;
			      mov2++;
			      memcpy(mov2, end, len_end);
			      tail=(unsigned int) len << 3;
  
			      md5_reverse();
			      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			      refresh();
#endif
			      fflush(stdout);
			     }
			  
			}
		       
                       f=(char *)MIN;
		       if (len_begin) fast=0;
		       if (len<4+offset) 
			 {
			  fast=0;
			  len++;
			  total[len]=0x80;
			  mov2++;
			  memcpy(mov2, end, len_end);
			  tail=(unsigned int) len << 3;
		       
			  md5_reverse();
			  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			  refresh();
#endif
			  fflush(stdout);
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
		      
		      md5_reverse();
		      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		      refresh();
#endif
		      fflush(stdout);
		     }
		   if (len_begin>2)
		     md5_reverse();
		}
	     
              d=(char *)MIN;
      
	      if (len<6+offset) 
		{
		 len++;
		 total[len]=0x80;
		 mov2++;
		 memcpy(mov2, end, len_end);
		 tail=(unsigned int) len << 3;
		 
		 md5_reverse();
		 printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		 refresh();
#endif
		 fflush(stdout);
		}
	      if (len_begin>1)
		md5_reverse();
	    }
	  
          c=(char *)MIN;
	
          if (len<7+offset) 
	    {
	     len++;
	     total[len]=0x80;
	     mov2++;
	     memcpy(mov2, end, len_end);
	     tail=(unsigned int) len << 3;
	    
	     md5_reverse();
	     printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	     refresh();
#endif
	     fflush(stdout);
	    }

	  if (len_begin)
	    md5_reverse();
	}
     
      b=(char *)MIN;
     
      if (len<8+offset) 
	{
	  len++;
	  total[len]=0x80;
	  mov2++;
	  memcpy(mov2, end, len_end);
	  tail=(unsigned int) len << 3;
	 
	  md5_reverse();
	  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	  refresh();
#endif
	  fflush(stdout);
	}
      if (len_begin)
	md5_reverse();
    }

  return(0);
}






 int core1b(void)
{
  register unsigned int a;
  register unsigned int	b;
  register unsigned int	c;
  register unsigned int	d;



   

  b = 0xefcdab89;
  c = 0x98badcfe;
  d = 0x10325476; 
  

  a = 0xd76aa477 + x1[0];  
  a = NROTATE_LEFT (a, S11, SS11);
  a += b; 





  NFF (d, a, b, c, x1[1], S12, SS12, 0xe8c7b756);  /* 2  */
  NFF (c, d, a, b, x1[2], S13, SS13, 0x242070db); /* 3  */
  NFF0 (b, c, d, a, S14, SS14, 0xc1bdceee);      /* 4  */
  NFF0 (a, b, c, d, S11, SS11, 0xf57c0faf);      /* 5  */
  NFF0 (d, a, b, c, S12, SS12, 0x4787c62a);      /* 6  */
  NFF0 (c, d, a, b, S13, SS13, 0xa8304613);      /* 7  */
  NFF0 (b, c, d, a, S14, SS14, 0xfd469501);      /* 8  */
  NFF0 (a, b, c, d, S11, SS11, 0x698098d8);      /* 9  */
  NFF0 (d, a, b, c, S12, SS12, 0x8b44f7af);      /* 10 */
  NFF0 (c, d, a, b, S13, SS13, 0xffff5bb1);      /* 11 */
  NFF0 (b, c, d, a, S14, SS14, 0x895cd7be);      /* 12 */
  NFF0 (a, b, c, d, S11, SS11, 0x6b901122);      /* 13 */
  NFF0 (d, a, b, c, S12, SS12, 0xfd987193);      /* 14 */
  NFF (c, d, a, b, tail, S13, SS13, 0xa679438e); /* 15 */
  NFF0 (b, c, d, a, S14, SS14, 0x49b40821);      /* 16 */
  


  /*

    Round 2

  */
  
  NGG (a, b, c, d, x1[1], S21, SS21, 0xf61e2562);  /* 17 */
  NGG0 (d, a, b, c,  S22, SS22, 0xc040b340);       /* 18 */
  NGG0 (c, d, a, b, S23, SS23, 0x265e5a51);        /* 19 */
  NGG (b, c, d, a, x1[0], S24, SS24, 0xe9b6c7aa); /* 20 */
  NGG0 (a, b, c, d, S21, SS21, 0xd62f105d);        /* 21 */
  NGG0 (d, a, b, c, S22, SS22,  0x2441453);        /* 22 */
  NGG0 (c, d, a, b, S23, SS23, 0xd8a1e681);        /* 23 */
  NGG0 (b, c, d, a, S24, SS24, 0xe7d3fbc8);        /* 24 */
  NGG0 (a, b, c, d, S21, SS21, 0x21e1cde6);        /* 25 */
  NGG (d, a, b, c, tail, S22, SS22, 0xc33707d6);   /* 26 */
  NGG0 (c, d, a, b, S23, SS23, 0xf4d50d87);        /* 27 */
  NGG0 (b, c, d, a, S24, SS24, 0x455a14ed);        /* 28 */
  NGG0 (a, b, c, d, S21, SS21, 0xa9e3e905);        /* 29 */
  NGG (d, a, b, c, x1[2], S22, SS22, 0xfcefa3f8);  /* 30 */
  NGG0 (c, d, a, b, S23, SS23, 0x676f02d9);        /* 31 */
  NGG0 (b, c, d, a, S24, SS24, 0x8d2a4c8a);        /* 32 */
  
 

  /*

    Round 3

  */

  NHH0 (a, b, c, d, S31, SS31, 0xfffa3942);        /* 33 */
  NHH0 (d, a, b, c, S32, SS32, 0x8771f681);        /* 34 */
  NHH0 (c, d, a, b, S33, SS33, 0x6d9d6122);        /* 35 */
  NHH (b, c, d, a, tail, S34, SS34, 0xfde5380c);   /* 36 */
  NHH (a, b, c, d, x1[1], S31, SS31, 0xa4beea44);  /* 37 */
  NHH0 (d, a, b, c, S32, SS32, 0x4bdecfa9);        /* 38 */
  NHH0 (c, d, a, b, S33, SS33, 0xf6bb4b60);        /* 39 */
  NHH0 (b, c, d, a, S34, SS34, 0xbebfbc70);        /* 40 */
  NHH0 (a, b, c, d, S31, SS31, 0x289b7ec6);        /* 41 */
  NHH (d, a, b, c, x1[0], S32, SS32, 0xeaa127fa); /* 42 */
  NHH0 (c, d, a, b, S33, SS33, 0xd4ef3085);        /* 43 */
  NHH0 (b, c, d, a, S34, SS34,  0x4881d05);        /* 44 */
  NHH0 (a, b, c, d, S31, SS31, 0xd9d4d039);        /* 45 */



 
  if (!fast)
    {
          fasta = working[0]; 
 	  fastb = working[1]; 
 	  fastc = working[2]; 
 	  fastd = working[3];
 
	  fast=1;

	  fastb -= x1[1];

	  NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0xffeff47d); /* 55 */
	  NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0x8f0ccc92); /* 54 */
	  NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0x655b59c3); /* 53 */
	  NRII0 (fastb, fastc, fastd, fasta, S44, SS44, 0xfc93a039); /* 52 */
	  NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0xab9423a7); /* 51 */

	  fastc -= tail; 
	  
	  NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0x432aff97); /* 50 */
	  NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0xf4292244); /* 49 */


	
    }
  


 if (fasta != (a+x1[0]))
	  return 0;
 
 

 NHH0 (d, a, b, c, S32, SS32, 0xe6db99e5);          /* 46 */
 NHH0 (c, d, a, b, S33, SS33, 0x1fa27cf8);          /* 47 */ 
 NHH (b, c, d, a, x1[2], S34, SS34, 0xc4ac5665);    /* 48 */ 
 




 if ((fastb == b) && (fastc == c) && (fastd == d))
   return 1; 
 
 
 return 0;
}



















































