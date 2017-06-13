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


int core2();
void md5_reverse2(unsigned int*);



/* passwords <= 28 bytes (end) */
/* OK */



int crack_core2(input, resume)
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
  register unsigned int len_end=0;
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
  
  
  fast=0;
  
  
  
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
      strncpy(test, resume, len);
      
    }
  else
    {  
      offset+=len_end=strlen(end);
            
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
      strncpy(mov2, end, len_end);
    }


   digest2[0] -= 0x67452301;
   digest2[1] -= 0xefcdab89;  
   digest2[2] -= 0x98badcfe;  
   digest2[3] -= 0x10325476;



   md5_reverse2(digest2);


  total=test;
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
			      for(;h<(char *)MAX;h+=2)
				{
firsttime:	       		  *test=*h;
			

			       
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 28);
#endif


				 diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));
				  
                                  count+=2;
				 
                                  if (val=core2())
				    {
				      if (val==1)
					{
					  total[len]=0x00;
					  
					  if (!stats(total, len))
					    mdmesg(8, NULL);
					  if (!all)
					    return(1);
					  total[len]=0x80;			      
					}                  
				      else
					{
					  total[len]=0x00;
					  val=2;
					  if (!stats(total, len))
					    mdmesg(8, NULL);					
					  if (!all)
					    return(1);
					  total[len]=0x80;			      
					}
				    }

               
				}
                              h=(char *)MIN;
			      if (len<2+offset) 
				{
				  len++;
				  mov2++;
				  fast=0;
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
			      fast=0;
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
			  fast=0;
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
		  fast=0;
		  if (len<5+offset) 
		    {
		      len++;
		      mov2++;
		      
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




void md5_reverse2(unsigned int *hash)
{
  fasta = hash[0];
  fastb = hash[1];
  fastc = hash[2];
  fastd = hash[3];

  NRII0 (fastb, fastc, fastd, fasta, S44, SS44, 0xeb86d391);         /* 64 */
  NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0x2ad7d2bb);         /* 63 */

  working[0] = fasta;
  working[1] = fastb;
  working[2] = fastc;
  working[3] = fastd;
}




int core2()
{
  register unsigned int a, b, c, d;
  register unsigned int a1, b1, c1, d1;



  b = 0xefcdab89;
  b1=b;
  c = 0x98badcfe;
  c1=c;
  d = 0x10325476; 
  d1=d;
  

  a = 0xd76aa477 + x1[0]; 
  a1 = 0xd76aa477 + x1[0] + diff; 
  a = NROTATE_LEFT (a, S11, SS11);
  a1 = NROTATE_LEFT (a1, S11, SS11);
  a += b; 
  a1 += b;


	
  /* Round 1 */
  
  DNFF (d, a, b, c, x1[1], S12, SS12, 0xe8c7b756, d1, a1, b, c);  /* 2  */
  DNFF (c, d, a, b, x1[2], S13, SS13, 0x242070db, c1, d1, a1, b);  /* 3  */
  DNFF (b, c, d, a, x1[3], S14, SS14, 0xc1bdceee, b1, c1, d1, a1);  /* 4  */
  DNFF (a, b, c, d, x1[4], S11, SS11, 0xf57c0faf, a1, b1, c1, d1);  /* 5  */
  DNFF (d, a, b, c, x1[5], S12, SS12, 0x4787c62a, d1, a1, b1, c1);  /* 6  */
  DNFF (c, d, a, b, x1[6], S13, SS13, 0xa8304613, c1, d1, a1, b1);  /* 7  */
  DNFF0 (b, c, d, a,  S14, SS14, 0xfd469501, b1, c1, d1, a1);       /* 8  */
  DNFF0 (a, b, c, d, S11, SS11, 0x698098d8, a1, b1, c1, d1);        /* 9  */
  DNFF0 (d, a, b, c, S12, SS12, 0x8b44f7af, d1, a1, b1, c1);        /* 10 */
  DNFF0 (c, d, a, b, S13, SS13, 0xffff5bb1, c1, d1, a1, b1);        /* 11 */
  DNFF0 (b, c, d, a, S14, SS14, 0x895cd7be, b1, c1, d1, a1);        /* 12 */
  DNFF0 (a, b, c, d, S11, SS11, 0x6b901122, a1, b1, c1, d1);        /* 13 */
  DNFF0 (d, a, b, c, S12, SS12, 0xfd987193, d1, a1, b1, c1);        /* 14 */
  DNFF (c, d, a, b, tail, S13, SS13, 0xa679438e, c1, d1, a1, b1);   /* 15 */
  DNFF0 (b, c, d, a, S14, SS14, 0x49b40821, b1, c1, d1, a1);        /* 16 */

 /* Round 2 */
  DNGG (a, b, c, d, x1[1], S21, SS21, 0xf61e2562, a1, b1, c1, d1);  /* 17 */
  DNGG (d, a, b, c, x1[6], S22, SS22, 0xc040b340, d1, a1, b1, c1);  /* 18 */
  DNGG0 (c, d, a, b, S23, SS23, 0x265e5a51, c1, d1, a1, b1);        /* 19 */
  NDNGG (b, c, d, a, x1[0], S24, SS24, 0xe9b6c7aa, b1, c1, d1, a1); /* 20 */
  DNGG (a, b, c, d, x1[5], S21, SS21, 0xd62f105d, a1, b1, c1, d1);  /* 21 */
  DNGG0 (d, a, b, c, S22,  SS22, 0x2441453, d1, a1, b1, c1);        /* 22 */
  DNGG0 (c, d, a, b, S23, SS23, 0xd8a1e681, c1, d1, a1, b1);        /* 23 */
  DNGG (b, c, d, a, x1[4], S24, SS24, 0xe7d3fbc8, b1, c1, d1, a1);  /* 24 */
  DNGG0 (a, b, c, d, S21, SS21, 0x21e1cde6, a1, b1, c1, d1);        /* 25 */
  DNGG (d, a, b, c, tail, S22, SS22, 0xc33707d6, d1, a1, b1, c1);   /* 26 */
  DNGG (c, d, a, b, x1[3], S23, SS23, 0xf4d50d87, c1, d1, a1, b1);  /* 27 */
  DNGG0 (b, c, d, a, S24, SS24, 0x455a14ed, b1, c1, d1, a1);        /* 28 */
  DNGG0 (a, b, c, d, S21, SS21, 0xa9e3e905, a1, b1, c1, d1);        /* 29 */
  DNGG (d, a, b, c, x1[2], S22, SS22, 0xfcefa3f8, d1, a1, b1, c1);  /* 30 */
  DNGG0 (c, d, a, b, S23, SS23, 0x676f02d9, c1, d1, a1, b1);        /* 31 */
  DNGG0 (b, c, d, a, S24, SS24, 0x8d2a4c8a, b1, c1, d1, a1);        /* 32 */

  /* Round 3 */
  DNHH (a, b, c, d, x1[5], S31, SS31, 0xfffa3942, a1, b1, c1, d1);  /* 33 */
  DNHH0 (d, a, b, c, S32, SS32, 0x8771f681, d1, a1, b1, c1);        /* 34 */
  DNHH0 (c, d, a, b, S33, SS33, 0x6d9d6122, c1, d1, a1, b1);        /* 35 */
  DNHH (b, c, d, a, tail, S34, SS34, 0xfde5380c, b1, c1, d1, a1);   /* 36 */
  DNHH (a, b, c, d, x1[1], S31, SS31, 0xa4beea44, a1, b1, c1, d1);  /* 37 */
  DNHH (d, a, b, c, x1[4], S32, SS32, 0x4bdecfa9, d1, a1, b1, c1);  /* 38 */
  DNHH0 (c, d, a, b, S33, SS33, 0xf6bb4b60, c1, d1, a1, b1);        /* 39 */
  DNHH0 (b, c, d, a, S34, SS34, 0xbebfbc70, b1, c1, d1, a1);        /* 40 */
  DNHH0 (a, b, c, d, S31, SS31, 0x289b7ec6, a1, b1, c1, d1);        /* 41 */
  NDNHH (d, a, b, c, x1[0], S32, SS32, 0xeaa127fa, d1, a1, b1, c1); /* 42 */
  DNHH (c, d, a, b, x1[3], S33, SS33, 0xd4ef3085, c1, d1, a1, b1);  /* 43 */
  DNHH (b, c, d, a, x1[6], S34,  SS34, 0x4881d05, b1, c1, d1, a1);  /* 44 */
  DNHH0 (a, b, c, d, S31, SS31, 0xd9d4d039, a1, b1, c1, d1);        /* 45 */


  /* Round 4 */


  if (!fast)
    {
      fasta = working[0];
      fastb = working[1];
      fastc = working[2];
      fastd = working[3];

      fastc -= x1[2];
      NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0xbd3af235);       /* 62 */
      NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0xf7537e82);       /* 61 */
      fasta -= x1[4];
      NRII0 (fastb, fastc, fastd, fasta, S44, SS44, 0x4e0811a1);       /* 60 */
      NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0xa3014314);       /* 59 */
      fastc -= x1[6];
      NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0xfe2ce6e0);       /* 58 */
      NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0x6fa87e4f);       /* 57 */
      NRII0 (fastb, fastc, fastd, fasta, S44, SS44, 0x85845dd1);       /* 56 */
      fastb -= x1[1];
      NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0xffeff47d);       /* 55 */
      NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0x8f0ccc92);       /* 54 */
      fastd -= x1[3];
      NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0x655b59c3);       /* 53 */
      NRII0 (fastb, fastc, fastd, fasta, S44, SS44, 0xfc93a039);       /* 52 */
      fastb -= x1[5];
      NRII0 (fastc, fastd, fasta, fastb, S43, SS43, 0xab9423a7);       /* 51 */
      fastc -= tail;
      NRII0 (fastd, fasta, fastb, fastc, S42, SS42, 0x432aff97);       /* 50 */
      NRII0 (fasta, fastb, fastc, fastd, S41, SS41, 0xf4292244);       /* 49 */
 

      fast=1;
    }


  if ((fasta != a+x1[0]) && (fasta != a1+x1[0]+diff)) return(0);

  DNHH0 (d, a, b, c, S32, SS32, 0xe6db99e5, d1, a1, b1, c1);        /* 46 */
  DNHH0 (c, d, a, b, S33, SS33, 0x1fa27cf8, c1, d1, a1, b1);        /* 47 */
  DNHH (b, c, d, a, x1[2], S34, SS34, 0xc4ac5665, b1, c1, d1, a1);  /* 48 */

 
  if ((fastb == b) && (fastc == c) && (fastd == d)) return(1);
  if ((fastb == b1) && (fastc == c1) && (fastd ==d1)) return(2);

  return(0); 

}


