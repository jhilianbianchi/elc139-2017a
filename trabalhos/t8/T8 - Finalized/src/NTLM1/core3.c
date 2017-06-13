#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "generic.h"
#include "global.h"



void coreNTLM3();
extern unsigned int ascci2unicode(char *);
extern unsigned int unicode2ascii(char *, unsigned int);





/* passwords <= 56 bytes (end) */
/* 
   OK 
*/


int crack_NTLM_core3(input, resume)
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
  char *mov2, *tempo;
  char digest[16];
  struct timeval *tp;
  unsigned int size=56;



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


  /* unicode conversions */
    
  len_end=0;

  if (ender)
    len_end=ascii2unicode(end);


  if (len_end+18>size)
    {
      mdmesg(11, NULL);
      doexit();
    }
   

  
  if (resume[0])
    {

      len=ascii2unicode(resume);
 
      offset=0;
      if (ender) 
	offset+=len_end;

      len-=offset;
      
      for (i=0; i<len; i+=2)
	for (j=1;j<=strlen(alfa+1);j++)
	  if (resume[i]==alfa[j])
            { 
	      if (!i)   h=alfa+j;
	      if (i==2) g=alfa+j;
	      if (i==4) f=alfa+j;
	      if (i==6) e=alfa+j;
	      if (i==8) d=alfa+j;
	      if (i==10) c=alfa+j;
	      if (i==12) b=alfa+j;
	      if (i==14) a=alfa+j;
            }
      mov2=test+len;

      len += offset;
      memcpy(test, resume, len);

      total=test;
    }
  else
    {
      h=(char *)MIN;
      offset=0;
      if (ender) 
	offset+=len_end;

      total=test;
      
      if (minimal)
	{
	  for (i=0; i<8; i++)
	    {
	     
	      switch(minimal-i+95)
		{
		case 'a':
		  g++;
		  *(test+2)=*g;
		  break;
		  
		case 'b':
		  f++;
		  *(test+4)=*f;
		  break;
		  
		case 'c':
		  e++;
		  *(test+6)=*e;
		  break;
		  
		case 'd':
		  d++;
		  *(test+8)=*d;
		  break;
		  
		case 'e':
		  c++;
		  *(test+10)=*c;
		  break;
		  
		case 'f':
		  b++;
		  *(test+12)=*b;
		  break;
		  
		case 'g':
		  a++;
		  *(test+14)=*a;
		  break;
		  
		}
	    }
	  len=minimal*2;
	}
      else
	len=2;  

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
  Decode(x1, total, 56);
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
       *(test+14)=*a;
      for(;b<(char *)MAX;b++)
	{
	  *(test+12)=*b;
	  for(;c<(char *)MAX;c++)
	    {
	      *(test+10)=*c;
	      for(;d<(char *)MAX;d++)
		{
		  *(test+8)=*d;
		  for(;e<(char *)MAX;e++)
		    {
		      *(test+6)=*e;
		      for(;f<(char *)MAX;f++)
			{
			  *(test+4)=*f;
			  for(;g<(char *)MAX;g++)
			    {
			      *(test+2)=*g;
			      for(;h<(char *)MAX;h+=2)
				{
firsttime:     			  *test=*h;

                                   diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));				 
				  
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif

				  coreNTLM3();       
                                  count+=2;
				 
                                  if ((*digest2==*result2)&&(*(digest2+1)==*(result2+1))&&(*(digest2+2)==*(result2+2))&&(*(digest2+3)==*(result2+3)))
				    {
				     
				      val=1;
				      				      
				      if (!stats(total, len))
					mdmesg(8, NULL);
				      
				      if (!all)
					return(1);
				     
				    }
				  else
				    if ((*digest2==*result3)&&(*(digest2+1)==*(result3+1))&&(*(digest2+2)==*(result3+2))&&(*(digest2+3)==*(result3+3)))
				      {
				      
					val=2;
					
					if (!stats(total, len))
					  mdmesg(8, NULL);
					
					if (!all)
					  return(1);
				       
				      }
				  
				}
                              h=(char *)MIN;
			      if (len<4+offset) 
				{
				  len+=2;
				  mov2+=2;
				  if (ender)
				    memcpy(mov2, end, len_end); 
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
			  if (len<6+offset) 
			    {
			      len+=2;
			      mov2+=2;
			      if (ender)
				memcpy(mov2, end, len_end); 
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
		      if (len<8+offset) 
			{
			  len+=2;
			  mov2+=2;
			  if (ender)
			    memcpy(mov2, end, len_end); 
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
		  if (len<10+offset) 
		    {
		      len+=2;
		      mov2+=2;
		      if (ender)
			memcpy(mov2, end, len_end); 
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
              if (len<12+offset) 
		{
		  len+=2;
		  mov2+=2;
		  if (ender)
		    memcpy(mov2, end, len_end); 
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
	  if (len<14+offset) 
	    {
	      len+=2;
	      mov2+=2;
	      if (ender)
		memcpy(mov2, end, len_end); 
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
      if (len<16+offset) 
	{
	  len+=2;
	  mov2+=2;

	  if (ender)
	    memcpy(mov2, end, len_end); 

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






/* Crack verbosely all size  (end) */
/* OK */





int crack_verbose_NTLM_core3(input, resume)
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
  char *mov;
  char digest[16];
  struct timeval *tp;
  unsigned int size=56, w, q;
  unsigned char byte1, byte2, byte3, byte4;
  char *tempo;

  tp=(struct timeval *)malloc(sizeof(struct timeval)); 

  if (!tp)
   {
     mdmesg(7, NULL);
     exit(0);
   }

  bzero(digest, 16);
  mov=digest;
  copy=input;
  strncpy(target, input, 32);
  
  a=b=c=d=e=f=g=(char *)alfa;
  h=(char *)MIN;
  
  up2low(input);
  ascii2bin(copy, conv, mov);
  Decode(digest2, mov, 16);  
  
  test=(char *)malloc(size);

  if (!test)
    {
      mdmesg(7, NULL);
      doexit();
    }
  bzero(test, size);
  

  /* unicode conversions */

  len_end=0;

  if (ender)
      len_end=ascii2unicode(end);



  if (len_end+18>size)
    {
      mdmesg(11, NULL);
      doexit();
    }
   
    

  if (resume[0])
    {
      offset=0;
      if (ender) 
	offset+=len_end;

      len=(ascii2unicode(resume))-offset;
            
      for (i=0; i<len; i+=2)
	for (j=1;j<=strlen(alfa+1);j++)
	  if (resume[i]==alfa[j])
            { 
	      if (!i)   h=alfa+j;
	      if (i==2) g=alfa+j;
	      if (i==4) f=alfa+j;
	      if (i==6) e=alfa+j;
	      if (i==8) d=alfa+j;
	      if (i==10) c=alfa+j;
	      if (i==12) b=alfa+j;
	      if (i==14) a=alfa+j;
            }
      mov=test+len;
      len+=offset;
      memcpy(test, resume, len);
      total=test;
    }
  else
    {
      offset=0;
      
      if (ender) 
	offset+=len_end;
     
      total=test;

      if (minimal)
	{
	  for (i=0; i<8; i++)
	    {
	      switch(minimal-i+95)
		{
		case 'a':
		  g++;
  		  *(test+2)=*g;
		  break;
		  
		case 'b':
		  f++;
		  *(test+4)=*f;
		  break;
		  
 		case 'c':
		  e++;
		  *(test+6)=*e;
		  break;
		  
		case 'd':
		  d++;
		  *(test+8)=*d;
		  break;
		  
		case 'e':
		  c++;
		  *(test+10)=*c;
		  break;
		  
		case 'f':
		  b++;
		  *(test+12)=*b;
		  break;
		  
		case 'g':
		  a++;
		  *(test+14)=*a;
		  break;
		  
		}
	    }
	  len=minimal*2;
	}
      else
	len=2;  

      mov=test+len;
      len += offset;
      if (ender)
	memcpy(mov, end, len_end);
    }



 
#ifdef ISBIG_ENDIAN
  Decode(x1, total, 56);
#else
  x1=(unsigned int *)total;
#endif

  tail=len<<3;
  total[len]=0x80;
  
#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif


  
  if (hwrite)
    {
      if (fastwrite)
	fwrite(YES, sizeof(char), 1, desw);
      else
	fwrite(NO, sizeof(char), 1, desw);

      fwrite("\0", sizeof(char), 1, desw); 
      fwrite((char *) &len, sizeof(char), 1, desw);
    }
  
  if (benchmode)
    {
      alarm(duration);
      signal(SIGALRM, handle);
    }
  
  signal(SIGINT, handle);
  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;


  goto firsttime;
  
  for(;a<(char *)MAX;a++)
    {
       *(test+14)=*a;
      for(;b<(char *)MAX;b++)
	{
	  *(test+12)=*b;
	  for(;c<(char *)MAX;c++)
	    {
	      *(test+10)=*c;
	      for(;d<(char *)MAX;d++)
		{
		  *(test+8)=*d;
		  for(;e<(char *)MAX;e++)
		    {
		      *(test+6)=*e;
		      for(;f<(char *)MAX;f++)
			{
			  *(test+4)=*f;
			  for(;g<(char *)MAX;g++)
			    {
			      *(test+2)=*g;
			      for(;h<(char *)MAX;h+=2)
				{
firsttime:	      		  *test=*h;

                                  diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));
				
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif

                                  coreNTLM3();
				  
		                                       
#ifdef NCURSES
				  for (q=0,w=0; w<len; w+=2,q++)
				  mvwprintw(stdscr, 8, 25+q, "%c", total[w]);
				  mvwprintw(stdscr, 8, 59, " <-- string.");

				  mvwprintw(stdscr, 9, 25, "%c", *(total)+diff);
				  for (q=0,w=2; w<len; w+=2,q++)
				    mvwprintw(stdscr, 9, 26+q, "%c", total[w]);
				  mvwprintw(stdscr, 9, 59, " <-- string.");
				
#else
				  printw("\n");
				  for (w=0; w<len; w+=2)
				    printw("%c", total[w]);
				  printw(" <-- string.");
				  printw("\n%c", *(total)+diff);
				  for (w=2; w<len; w+=2)
				    printw("%c", total[w]);
				  printw(" <-- string.");
#endif

				  if (verbosity==2)
				    {
#ifdef NCURSES			
				      attrset(COLOR_PAIR(1));	  
				      hashprintw(result2, 10, 25);
				      mvwprintw(stdscr, 10, 59, " <-- hash.");
				      hashprintw(result3, 11, 25);
				      mvwprintw(stdscr, 11, 59, " <-- hash.");
				      attrset(COLOR_PAIR(1)|A_BOLD);
				      hashprintw(digest2, 12, 25);
				      mvwprintw(stdscr, 12, 59, " <-- reference.");
				      attrset(COLOR_PAIR(1));
#else
				      printf("\n");
				      hashprint(result2);
				      printf(" <-- hash.\n"); 
				      hashprint(result3);
				      printf(" <-- hash.\n"); 
				      hashprint(digest2);
				      printw(" <-- reference.\n\n");
#endif
				    }
				  
#ifdef NCURSES
				  refresh();
#else
                                  fflush(stdout);
#endif
				  
                                  count+=2;
				  
                                  if ((*digest2==*result2)&&(*(digest2+1)==*(result2+1))&&(*(digest2+2)==*(result2+2))&&(*(digest2+3)==*(result2+3)))
				    {
				     val=1;
				   
				     if (!stats(total, len))
				       mdmesg(8, NULL);
					
                                      if (!all)
					return(1);
				     
				    }     
				  else
				    if ((*digest2==*result3)&&(*(digest2+1)==*(result3+1))&&(*(digest2+2)==*(result3+2))&&(*(digest2+3)==*(result3+3)))
				      {
				      
					val=2;
					
					if (!stats(total, len))
					  mdmesg(8, NULL);
				      
					if (!all)
					  return(1);
				       
				      }                            
				 
				}
                              h=(char *)MIN;
			      if (len<4+offset) 
				{
				   len+=2;
				   mov+=2;
				   total[len]=0x80;

				   if (ender)
				     memcpy(mov, end, len_end);
				   
				   if (hwrite)
				     {
				       fwrite("\0", sizeof(char), 1, desw); 
				       fwrite((char *) &len, sizeof(char), 1, desw);
				     }
				   tail=len<<3;
				}
			    }
                           g=(char *)MIN;
			   if (len<6+offset) 
			     {
			       	len+=2;
				mov+=2;
				total[len]=0x80;
				
				if (ender)
				  memcpy(mov, end, len_end);
				
				if (hwrite)
				  {
				    fwrite("\0", sizeof(char), 1, desw); 
				    fwrite((char *) &len, sizeof(char), 1, desw);
				  }
			        tail=len<<3;
			     }
			}
                       f=(char *)MIN;
		       if (len<8+offset) 
			 {
			    len+=2;
			    mov+=2;
			    total[len]=0x80;
			
			    if (ender)
			      memcpy(mov, end, len_end);
			    
			    if (hwrite)
			      {
				fwrite("\0", sizeof(char), 1, desw); 
				fwrite((char *) &len, sizeof(char), 1, desw);
			      }
			    tail=len<<3;
			 }
		    }
                   e=(char *)MIN;
		   if (len<10+offset) 
		     {
		       	len+=2;
			mov+=2;
			total[len]=0x80;
			
			if (ender)
			  memcpy(mov, end, len_end);
			
			if (hwrite)
			  {
			    fwrite("\0", sizeof(char), 1, desw); 
			    fwrite((char *) &len, sizeof(char), 1, desw);
			  }
		        tail=len<<3;
		     }
		}
              d=(char *)MIN;
              if (len<12+offset) 
		{
		   len+=2;
		   mov+=2;
		   total[len]=0x80;
		   
		   if (ender)
		     memcpy(mov, end, len_end);
		
		   if (hwrite)
		     {
		       fwrite("\0", sizeof(char), 1, desw); 
		       fwrite((char *) &len, sizeof(char), 1, desw);
		     }
		   tail=len<<3;
		}
	    }
          c=(char *)MIN;
	  if (len<14+offset) 
	    {
	      len+=2;
	      mov+=2;
	      total[len]=0x80;
	   
	      if (ender)
		memcpy(mov, end, len_end);
	      
	      if (hwrite)
		{
		  fwrite("\0", sizeof(char), 1, desw); 
		  fwrite((char *) &len, sizeof(char), 1, desw);
		}
	      tail=len<<3;
	    }
	}
      b=(char *)MIN;
      if (len<16+offset) 
	{
	   len+=2;
	   mov+=2;
	   total[len]=0x80;
	   
	   if (ender)
	     memcpy(mov, end, len_end);
	
	   if (hwrite)
	     {
	       fwrite("\0", sizeof(char), 1, desw); 
	       fwrite((char *) &len, sizeof(char), 1, desw);
	     }
	   tail=len<<3;
	}
    }

  return(0);

}







 void coreNTLM3(void)
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
 

  NDNFF (a, b, c, d, x1[0], S11, SS11, a1, b, c, d);         /* 1  */
  DNFF (d, a, b, c, x1[1], S12, SS12, d1, a1, b, c);         /* 2  */
  DNFF (c, d, a, b, x1[2], S13, SS13, c1, d1, a1, b);        /* 3  */
  DNFF (b, c, d, a, x1[3], S14, SS14, b1, c1, d1, a1);       /* 4  */
  DNFF (a, b, c, d, x1[4], S11, SS11, a1, b1, c1, d1);       /* 5  */
  DNFF (d, a, b, c, x1[5], S12, SS12, d1, a1, b1, c1);       /* 6  */
  DNFF (c, d, a, b, x1[6], S13, SS13, c1, d1, a1, b1);       /* 7  */
  DNFF (b, c, d, a, x1[7], S14, SS14, b1, c1, d1, a1);       /* 8  */
  DNFF (a, b, c, d, x1[8], S11, SS11, a1, b1, c1, d1);       /* 9  */
  DNFF (d, a, b, c, x1[9], S12, SS12, d1, a1, b1, c1);       /* 10 */
  DNFF (c, d, a, b, x1[10], S13, SS13, c1, d1, a1, b1);      /* 11 */
  DNFF (b, c, d, a, x1[11], S14, SS14, b1, c1, d1, a1);      /* 12 */
  DNFF (a, b, c, d, x1[12], S11, SS11, a1, b1, c1, d1);      /* 13 */
  DNFF (d, a, b, c, x1[13],S12, SS12,d1, a1, b1, c1);        /* 14 */
  DNFF (c, d, a, b, tail, S13, SS13, c1, d1, a1, b1);        /* 15 */
  DNFF0 (b, c, d, a, S14, SS14, b1, c1, d1, a1);             /* 16 */
  

  /*

    Round 2

  */

  
  NDNGG (a, b, c, d, x1[0], S21, SS21, a1, b1, c1, d1);      /* 17 */
  DNGG (d, a, b, c, x1[4], S22, SS22, d1, a1, b1, c1);       /* 18 */
  DNGG (c, d, a, b,x1[8], S23, SS23, c1, d1, a1, b1);        /* 19 */
  DNGG (b, c, d, a, x1[12], S24, SS24, b1, c1, d1, a1);      /* 20 */
  DNGG (a, b, c, d, x1[1], S21, SS21, a1, b1, c1, d1);       /* 21 */
  DNGG (d, a, b, c, x1[5], S22, SS22,  d1, a1, b1, c1);      /* 22 */
  DNGG (c, d, a, b, x1[9],S23, SS23, c1, d1, a1, b1);        /* 23 */
  DNGG (b, c, d, a, x1[13],S24, SS24, b1, c1, d1, a1);       /* 24 */
  DNGG (a, b, c, d, x1[2], S21, SS21, a1, b1, c1, d1);       /* 25 */
  DNGG (d, a, b, c,x1[6], S22, SS22, d1, a1, b1, c1);        /* 26 */
  DNGG (c, d, a, b, x1[10],S23, SS23, c1, d1, a1, b1);       /* 27 */
  DNGG (b, c, d, a, tail, S24, SS24, b1, c1, d1, a1);        /* 28 */
  DNGG (a, b, c, d, x1[3], S21, SS21, a1, b1, c1, d1);       /* 29 */
  DNGG (d, a, b, c, x1[7],S22, SS22, d1, a1, b1, c1);        /* 30 */
  DNGG (c, d, a, b, x1[11], S23, SS23, c1, d1, a1, b1);      /* 31 */
  DNGG0 (b, c, d, a, S24, SS24, b1, c1, d1, a1);             /* 32 */
  
 

  /*

    Round 3

  */

  NDNHH (a, b, c, d, x1[0], S31, SS31, a1, b1, c1, d1);     /* 33 */
  DNHH (d, a, b, c, x1[8],S32, SS32, d1, a1, b1, c1);       /* 34 */
  DNHH (c, d, a, b, x1[4], S33, SS33, c1, d1, a1, b1);      /* 35 */
  DNHH (b, c, d, a, x1[12], S34, SS34, b1, c1, d1, a1);     /* 36 */
  DNHH (a, b, c, d, x1[2], S31, SS31, a1, b1, c1, d1);      /* 37 */
  DNHH (d, a, b, c,x1[10], S32, SS32, d1, a1, b1, c1);      /* 38 */
  DNHH (c, d, a, b, x1[6],S33, SS33, c1, d1, a1, b1);       /* 39 */
  DNHH (b, c, d, a, tail, S34, SS34, b1, c1, d1, a1);       /* 40 */
  DNHH (a, b, c, d, x1[1], S31, SS31, a1, b1, c1, d1);      /* 41 */
  DNHH (d, a, b, c,x1[9], S32, SS32,d1, a1, b1, c1);        /* 42 */
  DNHH (c, d, a, b,x1[5], S33, SS33, c1, d1, a1, b1);       /* 43 */
  DNHH (b, c, d, a,x1[13], S34, SS34,  b1, c1, d1, a1);     /* 44 */
  DNHH (a, b, c, d, x1[3],S31, SS31, a1, b1, c1, d1);       /* 45 */
  DNHH (d, a, b, c,x1[11], S32, SS32, d1, a1, b1, c1);      /* 46 */
  DNHH (c, d, a, b, x1[7],S33, SS33, c1, d1, a1, b1);       /* 47 */ 
  DNHH0 (b, c, d, a, S34, SS34, b1, c1, d1, a1);            /* 48 */ 
 

  a  += 0x67452301;
  a1 += 0x67452301;
  b  += 0xefcdab89;
  b1 += 0xefcdab89;
  c  += 0x98badcfe;
  c1 += 0x98badcfe;
  d  += 0x10325476;
  d1 += 0x10325476;

 result2[0] = a;
 result2[1] = b;
 result2[2] = c; 
 result2[3] = d;

 result3[0] = a1;
 result3[1] = b1;
 result3[2] = c1; 
 result3[3] = d1;

}





