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



void core2b();




/* passwords <= 28 bytes (end/begin) */
/* OK */



int crack_begin_core2(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  register char *a,*b,*c,*d,*e,*f,*g,*h;
  char *copy;
  unsigned int offset=0;
  register int MAX=(unsigned int) alfa+strlen(alfa+1)+1;
  register int MIN=(unsigned int) alfa+1; 
  unsigned char i,j; 
  char *mov2;
  char digest[16];
  struct timeval *tp;
  register unsigned int len_begin=0, len_end=0;
  unsigned int size=28;


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

  a=b=c=d=e=f=g=(char *)alfa;
  h=(char *)MIN;


   if (resume[0])
    {

     offset=len_begin=strlen(begin);
     if (ender) offset+=len_end=strlen(end);
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
      h=(char *)MIN;
      offset=len_begin=strlen(begin);
      if (ender) 
	offset+=len_end=strlen(end);
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
      len += offset;
      if (ender) 
	memcpy(mov2, end, len_end);
    }
   


 
 
    

 
  tail=len<<3;
  total[len]=0x80;
  
 
  printw("\nPassword size: %u \n", len);

#ifdef NCURSES
  refresh();
#endif
  fflush(stdout);


 if (benchmode)
    {
     alarm(duration);
     signal(SIGALRM, handle);
    }



#ifdef ISBIG_ENDIAN
  Decode(x1, total, 28);
#else
  x1=(unsigned int *)total;
#endif


  signal(SIGINT, handle);
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
			
				
				 
                                  core2b();
			       
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 28);
#endif


                                  count++;
				 
                                  if (((*digest2==*result2)&&(*(digest2+1)==*(result2+1))&&(*(digest2+2)==*(result2+2))&&(*(digest2+3)==*(result2+3))))
				    {
				     total[len]=0x00;
				     val=1;
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
				  mov2++;
				  if (ender)
				    strncpy(mov2, end, len_end);
				  total[len]=0x80;		     
				  tail=len<<3;
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
			      mov2++;
			      if (ender)
				strncpy(mov2, end, len_end);
			      total[len]=0x80;
			      tail=len<<3;
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
			  mov2++;
			  if (ender)
			    strncpy(mov2, end, len_end);
			  total[len]=0x80;
			  tail=len<<3;
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
		      mov2++;
		      if (ender)
			strncpy(mov2, end, len_end);
		      total[len]=0x80;
		      tail=len<<3;
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
		  mov2++;
		  if (ender)
		    strncpy(mov2, end, len_end);
		  total[len]=0x80;
		  tail=len<<3;
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
	      mov2++;
	      if (ender)
		strncpy(mov2, end, len_end);
	      total[len]=0x80;
	      tail=len<<3;
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
	  mov2++;
	  if (ender)
	    strncpy(mov2, end, len_end);
	  total[len]=0x80;
	  tail=len<<3;
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






void core2b()
{
  register unsigned int a, b, c, d;
  register unsigned int a1, b1, c1, d1;

  a = 0x67452301;
  b = 0xefcdab89;
  c = 0x98badcfe;
  d = 0x10325476;
  	
  /* Round 1 */
  NFF (a, b, c, d, x1[0], S11, SS11, 0xd76aa478); /* 1  */
  NFF (d, a, b, c, x1[1], S12, SS12, 0xe8c7b756);  /* 2  */
  NFF (c, d, a, b, x1[2], S13, SS13, 0x242070db);  /* 3  */
  NFF (b, c, d, a, x1[3], S14, SS14, 0xc1bdceee);  /* 4  */
  NFF (a, b, c, d, x1[4], S11, SS11, 0xf57c0faf);  /* 5  */
  NFF (d, a, b, c, x1[5], S12, SS12, 0x4787c62a);  /* 6  */
  NFF (c, d, a, b, x1[6], S13, SS13, 0xa8304613);  /* 7  */
  NFF0 (b, c, d, a,  S14, SS14, 0xfd469501);       /* 8  */
  NFF0 (a, b, c, d, S11, SS11, 0x698098d8);        /* 9  */
  NFF0 (d, a, b, c, S12, SS12, 0x8b44f7af);        /* 10 */
  NFF0 (c, d, a, b, S13, SS13, 0xffff5bb1);        /* 11 */
  NFF0 (b, c, d, a, S14, SS14, 0x895cd7be);        /* 12 */
  NFF0 (a, b, c, d, S11, SS11, 0x6b901122);        /* 13 */
  NFF0 (d, a, b, c, S12, SS12, 0xfd987193);        /* 14 */
  NFF (c, d, a, b, tail, S13, SS13, 0xa679438e);   /* 15 */
  NFF0 (b, c, d, a, S14, SS14, 0x49b40821);        /* 16 */

 /* Round 2 */
  NGG (a, b, c, d, x1[1], S21, SS21, 0xf61e2562);  /* 17 */
  NGG (d, a, b, c, x1[6], S22, SS22, 0xc040b340);  /* 18 */
  NGG0 (c, d, a, b, S23, SS23, 0x265e5a51);        /* 19 */
  NGG (b, c, d, a, x1[0], S24, SS24, 0xe9b6c7aa); /* 20 */
  NGG (a, b, c, d, x1[5], S21, SS21, 0xd62f105d);  /* 21 */
  NGG0 (d, a, b, c, S22,  SS22, 0x2441453);        /* 22 */
  NGG0 (c, d, a, b, S23, SS23, 0xd8a1e681);        /* 23 */
  NGG (b, c, d, a, x1[4], S24, SS24, 0xe7d3fbc8);  /* 24 */
  NGG0 (a, b, c, d, S21, SS21, 0x21e1cde6);        /* 25 */
  NGG (d, a, b, c, tail, S22, SS22, 0xc33707d6);   /* 26 */
  NGG (c, d, a, b, x1[3], S23, SS23, 0xf4d50d87);  /* 27 */
  NGG0 (b, c, d, a, S24, SS24, 0x455a14ed);        /* 28 */
  NGG0 (a, b, c, d, S21, SS21, 0xa9e3e905);        /* 29 */
  NGG (d, a, b, c, x1[2], S22, SS22, 0xfcefa3f8);  /* 30 */
  NGG0 (c, d, a, b, S23, SS23, 0x676f02d9);        /* 31 */
  NGG0 (b, c, d, a, S24, SS24, 0x8d2a4c8a);        /* 32 */

  /* Round 3 */
  NHH (a, b, c, d, x1[5], S31, SS31, 0xfffa3942);  /* 33 */
  NHH0 (d, a, b, c, S32, SS32, 0x8771f681);        /* 34 */
  NHH0 (c, d, a, b, S33, SS33, 0x6d9d6122);        /* 35 */
  NHH (b, c, d, a, tail, S34, SS34, 0xfde5380c);   /* 36 */
  NHH (a, b, c, d, x1[1], S31, SS31, 0xa4beea44);  /* 37 */
  NHH (d, a, b, c, x1[4], S32, SS32, 0x4bdecfa9);  /* 38 */
  NHH0 (c, d, a, b, S33, SS33, 0xf6bb4b60);        /* 39 */
  NHH0 (b, c, d, a, S34, SS34, 0xbebfbc70);        /* 40 */
  NHH0 (a, b, c, d, S31, SS31, 0x289b7ec6);        /* 41 */
  NHH (d, a, b, c, x1[0], S32, SS32, 0xeaa127fa); /* 42 */
  NHH (c, d, a, b, x1[3], S33, SS33, 0xd4ef3085);  /* 43 */
  NHH (b, c, d, a, x1[6], S34,  SS34, 0x4881d05);  /* 44 */
  NHH0 (a, b, c, d, S31, SS31, 0xd9d4d039);        /* 45 */
  NHH0 (d, a, b, c, S32, SS32, 0xe6db99e5);        /* 46 */
  NHH0 (c, d, a, b, S33, SS33, 0x1fa27cf8);        /* 47 */
  NHH (b, c, d, a, x1[2], S34, SS34, 0xc4ac5665);  /* 48 */

  /* Round 4 */
  NII (a, b, c, d, x1[0], S41, SS41, 0xf4292244); /* 49 */
  NII0 (d, a, b, c, S42, SS42, 0x432aff97);        /* 50 */
  NII (c, d, a, b, tail, S43, SS43, 0xab9423a7);   /* 51 */
  NII (b, c, d, a, x1[5], S44, SS44, 0xfc93a039);  /* 52 */
  NII0 (a, b, c, d, S41, SS41, 0x655b59c3);        /* 53 */
  NII (d, a, b, c, x1[3], S42, SS42, 0x8f0ccc92);  /* 54 */
  NII0 (c, d, a, b, S43, SS43, 0xffeff47d);        /* 55 */
  NII (b, c, d, a, x1[1], S44, SS44, 0x85845dd1);  /* 56 */
  NII0 (a, b, c, d, S41, SS41, 0x6fa87e4f);        /* 57 */
  NII0 (d, a, b, c, S42, SS42, 0xfe2ce6e0);        /* 58 */
  NII (c, d, a, b, x1[6], S43, SS43, 0xa3014314);  /* 59 */
  NII0 (b, c, d, a, S44, SS44, 0x4e0811a1);        /* 60 */
  NII (a, b, c, d, x1[4], S41, SS41, 0xf7537e82);  /* 61 */
  NII0 (d, a, b, c, S42, SS42, 0xbd3af235);        /* 62 */
  NII (c, d, a, b, x1[2], S43, SS43, 0x2ad7d2bb);  /* 63 */
  NII0 (b, c, d, a, S44, SS44, 0xeb86d391);        /* 64 */


 
  *result2 = 0x67452301;
  *(result2+1) = 0xefcdab89;
  *(result2+2) = 0x98badcfe;
  *(result2+3) = 0x10325476;

  *result2 += a;
  *(result2+1) += b;
  *(result2+2) += c;
  *(result2+3) += d;

}

















