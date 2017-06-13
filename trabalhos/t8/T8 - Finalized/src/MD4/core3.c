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



void core43();
int core43bis();



int md43_reverse(unsigned int *hash)
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
 

  working[0]=fasta;
  working[1]=fastb;
  working[2]=fastc;
  working[3]=fastd; 

}


/* passwords <= 56 bytes (end) */
/* OK */


int crack4_core3(input, resume)
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
    md43_reverse(digest2);
    fast=0;

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
    tail=len<<3;
    total[len]=0x80;
  
    

  printw("\nPassword size: %u \n", len);


#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif

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
firsttime:	                  *test=*h;
				  diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));
				  
#ifdef ISBIG_ENDIAN 
				  Decode(x1, total, 56);
#endif
				  count +=2;

				  if (val=core43bis())
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






/* Crack verbosely all sized  (end|file) */
/* OK */





int crack4_verbose_core3(input, resume)
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
  register unsigned int len_end=0;
  unsigned int size=56;
  unsigned char byte1, byte2, byte3, byte4;
 


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
    h=(char *) MIN;
  


  test=(char *)malloc(size);
  if (!test)
   {
     mdmesg(7, NULL);
     doexit();
   }

  bzero(test, size);

  up2low(input);
  ascii2bin(copy, conv, mov);
  Decode(digest2, mov, 16);  



   if (resume[0])
    {    
if (ender)
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
     mov=test+len;
     len+=offset;
     strncpy(test, resume, len);
    }
  else
    {
if (ender)
     offset=len_end=strlen(end);

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
      
      mov=test+len;
      len += offset;
      if (ender) 
	memcpy(mov, end, len_end);
    }



 
  if (offset+9>56)
    {
      mdmesg(11, NULL);
      doexit();
    }

 
  total=test;
  tail=len<<3;
  total[len]=0x80;
 
#ifdef ISBIG_ENDIAN
  Decode(x1, total, 56);
#else
  x1=(unsigned int *)total;
#endif

 


#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif

  
 if (hwrite){
  if (fastwrite)
    fwrite(YES, sizeof(char), 1, desw);
  else
    fwrite(NO, sizeof(char), 1, desw);

  fwrite("\0", sizeof(char), 1, desw); 
  fwrite((char *) &len, sizeof(char), 1, desw);}

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
firsttime:			  *test=*h;
							  
				   diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));			 
				  total[len]=0x80;
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif
				 
                                  core43();
				  total[len]=0x00;
				
				  if (hwrite)
				  if (!fastwrite)
				  {
				    char new;

                                   fwrite(total, sizeof(char), len+1, desw);
                                   for (i=0; i<4; i++)
                                     {
	                              byte1=(unsigned char) ((result2[i])>>24);
	                              byte2=(unsigned char) ((result2[i]&0x00ff0000)>>16);
	                              byte3=(unsigned char) ((result2[i]&0x0000ff00)>>8);
	                              byte4=(unsigned char) ((result2[i])&0x000000ff);
                                      
    				      fprintf (desw,"%02x%02x%02x%02x",byte4, byte3, byte2, byte1);
				     }
                                   fwrite("\n", sizeof(char), 2, desw);

				   new=total[0]+diff;
				   fwrite(&new, sizeof(char), 1, desw);
				   fwrite(&total[1], sizeof(char), len, desw);
                                   for (i=0; i<4; i++)
                                     {
	                              byte1=(unsigned char) ((result3[i])>>24);
	                              byte2=(unsigned char) ((result3[i]&0x00ff0000)>>16);
	                              byte3=(unsigned char) ((result3[i]&0x0000ff00)>>8);
	                              byte4=(unsigned char) ((result3[i])&0x000000ff);
                                      
    				      fprintf (desw,"%02x%02x%02x%02x",byte4, byte3, byte2, byte1);
				     }
                                   fwrite("\n", sizeof(char), 2, desw);
				  }
				  else 
				  { 
				    char new;

				  fwrite(total, sizeof(char), len, desw);
				  fwrite(result2, sizeof(unsigned int), 4, desw);

				  new=total[0]+diff;
				  fwrite(&new, sizeof(char), 1, desw);
				  fwrite(&total[1], sizeof(char), len-1, desw);
				  fwrite(result3, sizeof(unsigned int), 4, desw);
				  }
                                
#ifdef NCURSES

				  mvwprintw(stdscr, 8, 25, "%s", total);
				  mvwprintw(stdscr, 8, 59, " <-- string.");
				  mvwprintw(stdscr, 9, 25, "%c", *(total)+diff);
				  mvwprintw(stdscr, 9, 26, "%s", &total[1]);
				  mvwprintw(stdscr, 9, 59, " <-- string.");
#else
				  printw("\n%s <-- string.", total);
				  printw("\n%c", *(total)+diff);
				  printw("%s <-- string.\n", &total[1]);
                                
#endif
				  if (verbosity==2)
				  {
#ifdef NCURSES
				    hashprintw(result2, 10, 25);
				    mvwprintw(stdscr, 10, 59, " <-- hash.");
				   
				    hashprintw(result3, 11, 25);
				    mvwprintw(stdscr, 11, 59, " <-- hash.");
				  
				    attrset(COLOR_PAIR(1)|A_BOLD);
				    hashprintw(digest2, 12, 25);
				    mvwprintw(stdscr, 12, 59, " <-- reference.");
				   
				    attrset(COLOR_PAIR(1));
#else
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
				     total[len]=0x00;
				     val=1;
				     if (!stats(total, len))
				       mdmesg(8, NULL);
					
                                     
                                      if (!all)
					return(1);
				       total[len]=0x80;
				    }                                 
				  else
				    if (((*digest2==*result3)&&(*(digest2+1)==*(result3+1))&&(*(digest2+2)==*(result3+2))&&(*(digest2+3)==*(result3+3))))
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
                              h=(char *)MIN;
			      if (len<2+offset) 
				{
				   len++;
				   mov++;
				   if (ender)
				     memcpy(mov, end, len_end);
				   if (hwrite){
				     fwrite("\0", sizeof(char), 1, desw); 
				     fwrite((char *) &len, sizeof(char), 1, desw);}
				   tail=len<<3;
				}
			    }
                           g=(char *)MIN;
			   if (len<3+offset) 
			     {
			       	len++;
				mov++;
				if (ender)
				  memcpy(mov, end, len_end);
				if (hwrite){
				  fwrite("\0", sizeof(char), 1, desw); 
				  fwrite((char *) &len, sizeof(char), 1, desw);}
			        tail=len<<3;
			     }
			}
                       f=(char *)MIN;
		       if (len<4+offset) 
			 {
			    len++;
			    mov++;
			    if (ender)
			      memcpy(mov, end, len_end);
			    if (hwrite){
			      fwrite("\0", sizeof(char), 1, desw); 
			      fwrite((char *) &len, sizeof(char), 1, desw);}
			    tail=len<<3;
			 }
		    }
                   e=(char *)MIN;
		   if (len<5+offset) 
		     {
		       	len++;
			mov++;
			if (ender)
			  memcpy(mov, end, len_end);
			if (hwrite){
			  fwrite("\0", sizeof(char), 1, desw); 
			  fwrite((char *) &len, sizeof(char), 1, desw);}
		        tail=len<<3;
		     }
		}
              d=(char *)MIN;
              if (len<6+offset) 
		{
		   len++;
		   mov++;
		   if (ender)
		     memcpy(mov, end, len_end);
		   if (hwrite){
		     fwrite("\0", sizeof(char), 1, desw); 
		     fwrite((char *) &len, sizeof(char), 1, desw);}
		   tail=len<<3;
		}
	    }
          c=(char *)MIN;
	  if (len<7+offset) 
	    {
	      len++;
	      mov++;
	      if (ender)
		memcpy(mov, end, len_end);
	      if (hwrite){
		fwrite("\0", sizeof(char), 1, desw); 
		fwrite((char *) &len, sizeof(char), 1, desw);}
	      tail=len<<3;
	    }
	}
      b=(char *)MIN;
      if (len<8+offset) 
	{
	   len++;
	   mov++;
	   if (ender)
	     memcpy(mov, end, len_end);
	   if (hwrite){
	     fwrite("\0", sizeof(char), 1, desw); 
	     fwrite((char *) &len, sizeof(char), 1, desw);}
	   tail=len<<3;
	}
    }

  return(0);

}




/* crack to file (file)*/
/*
  OK
*/


int crack4_write_core3(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  register char *a,*b,*c,*d,*e,*f,*g,*h;
  char *copy;
  register int MAX=(unsigned int) alfa+strlen(alfa+1)+1;
  register int MIN=(unsigned int) alfa+1; 
  unsigned char i,j; 
  unsigned int offset=0, len_begin=0, len_end=0;
  char *mov2;
  char digest[16];
  struct timeval *tp;
  char *bufferw;
  unsigned char byte1, byte2, byte3, byte4;
  unsigned int size=56, amount;
  float doff;
  char *bufferr;
  
 
  tp=(struct timeval *)malloc(sizeof(struct timeval));
  if (!tp)
   {
     mdmesg(7, NULL);
     doexit();
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

  total=test;
  bzero(test, size);
  



 if (resume[0])
    {
     
     if (ender)  
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
      
      if (ender) 
	offset=len_end=strlen(end);     


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




  

  bufferr=(char *)malloc((BLOCKSIZE/2)*1024*1024);
  if (!bufferr)
    {
      mdmesg(7, NULL);
      doexit();
    }
  if (fastwrite)
    mdmesg(23, NULL);
  else
    mdmesg(24, NULL);


  mdmesg(25, NULL);
  mdmesg(20, BLOCKSIZE);


#ifndef NCURSES
  fflush(NULL);
#else
  refresh();
#endif


  setvbuf(desw, NULL, _IONBF, 0);

  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;
  amount=fwrite(bufferr, sizeof(char), BLOCKSIZE*1024*1024, desw);
  gettimeofday(tp, NULL);
  elapsed=tp->tv_sec-start;
  elapsed_u=tp->tv_usec-start_u;
 

  if (elapsed_u < 0)
    {
     elapsed_u=1000000+elapsed_u;
     if (elapsed>0) elapsed--;
     }
     doff=(float)elapsed+((float) elapsed_u/(float)1000000);
     doff=((float) (amount/(1024*1024)) /doff);
     printw(" %.1f MB/sec.", doff);
    


#ifdef NCURSES
     refresh();
#else
     fflush(stdout);
#endif

    
  fseek(desw, 0, SEEK_SET);
  mdmesg(21, (BLOCKSIZE/2));


#ifdef ISBIG_ENDIAN
  bufferr=(char *)malloc((BLOCKSIZE/2)*1024*1024);
#else
  realloc(bufferr, (BLOCKSIZE/2)*1024*1024);
#endif

  
  fflush(NULL);
  setvbuf(desw, bufferr, _IOFBF, (BLOCKSIZE/2)*1024*1024); 
  
  signal(SIGINT, handle);
  if (benchmode)
    {
      alarm(duration);
      signal(SIGALRM, handle);
    }
  
  tail=len<<3;
  total[len]=0x80;
  
  printw("\nPassword size: %u \n", len);


#ifdef ISBIG_ENDIAN
  Decode(x1, total, 56);
#else
  x1=(unsigned int *)total;
#endif


#ifdef NCURSES
  refresh();
#else   
  fflush(stdout);
#endif

  if (fastwrite)
    fwrite(YES, sizeof(char), 1, desw);
  else
    fwrite(NO, sizeof(char), 1, desw);
  
  fwrite("\0", sizeof(char), 1, desw); 
  fwrite((char *) &len, sizeof(char), 1, desw);
  



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
firsttime:		       	  *test=*h;
				   diff=(signed int)((unsigned int)*(h+1)-(unsigned int)*(h));

				 

				  total[len]=0x80;
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif
                                  core43();
				  total[len]=0x00;

				  if (!fastwrite)
				    {
				      char new;
				      fwrite(total, sizeof(char), len+1, desw);
				      for (i=0; i<4; i++)
					{
					  byte1=(char) ((result2[i])>>24);
					  byte2=(char) ((result2[i]&0x00ff0000)>>16);
					  byte3=(char) ((result2[i]&0x0000ff00)>>8);
					  byte4=(char) ((result2[i])&0x000000ff);
					  
  
					  fprintf(desw, "%02x%02x%02x%02x", byte4, byte3, byte2, byte1);
					  
					}
				      fwrite("\n", sizeof(char), 2, desw);  

				      new=total[0]+diff;
				      fwrite(&new, sizeof(char), 1, desw);	
				      fwrite(&total[1], sizeof(char), len, desw);				      
				      for (i=0; i<4; i++)
					{
					  byte1=(char) ((result3[i])>>24);
					  byte2=(char) ((result3[i]&0x00ff0000)>>16);
					  byte3=(char) ((result3[i]&0x0000ff00)>>8);
					  byte4=(char) ((result3[i])&0x000000ff);
					  
					  
					  fprintf(desw, "%02x%02x%02x%02x", byte4, byte3, byte2, byte1);
					  
					}
				      fwrite("\n", sizeof(char), 2, desw);
				    }
				  else 
				    { 
				      char new;

				      fwrite(total, sizeof(char), len, desw);
				      fwrite(result2, sizeof(unsigned int), 4, desw);
				      
				      new=total[0]+diff;
				      fwrite(&new, sizeof(char), 1, desw);
				      fwrite(&total[1], sizeof(char), len-1, desw);
				      fwrite(result3, sizeof(unsigned int), 4, desw);
				    }
				  
                                  count+=2;
				  
				  if ((*digest2==*result2)&&(*(digest2+1)==*(result2+1))&&(*(digest2+2)==*(result2+2))&&(*(digest2+3)==*(result2+3)))
				    {
				      total[len]=0x00;
				      val=1;
				      if (!stats(total, len))
					mdmesg(8, NULL);
				      
				      
                                      if (!all)
                                        {
					  fclose(desw);
					  return(1);
					}
				      
				      total[len]=0x80;
				    }

				  else 
				    if ((*digest2==*result3)&&(*(digest2+1)==*(result3+1))&&(*(digest2+2)==*(result3+2))&&(*(digest2+3)==*(result3+3)))
				      {
					total[len]=0x00;
					val=2;
					if (!stats(total, len))
					  mdmesg(8, NULL);

					if (!all)
					  {
					    fclose(desw);
					    return(1);
					  }
					total[len]=0x80;
				      }
				}
                              h=(char *)MIN;
			      
			      if (len<2+offset)
			      {
			       len++; 
			       mov2++;
			       if (ender)
				 memcpy(mov2, end, len_end);
			       tail=len<<3;
                               total[len]=0x80;
			       
                               printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			       refresh();
#else
                               fflush(stdout);
#endif
			       fwrite("\0", sizeof(char), 1, desw); 
			       fwrite((char *) &len, sizeof(char), 1, desw);
			      }
			    }
			  g=(char *)MIN;

			  if (len<3+offset) 
			    {
			      len++; 
			      tail=len<<3;
			      total[len]=0x80;
			      mov2++;
			      if (ender)
				memcpy(mov2, end, len_end);
			      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			      refresh();
#else
                              fflush(stdout);
#endif
			      fwrite("\0", sizeof(char), 1, desw); 
			      fwrite((char *) &len, sizeof(char), 1, desw);
			    }
			}
		      f=(char *)MIN;

		      if (len<4+offset) 
			{
			  len++; 
			  tail=len<<3;
			  total[len]=0x80;
			  mov2++;
			  if (ender)
			    memcpy(mov2, end, len_end);
			  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
			  refresh();
#else
                          fflush(stdout);
#endif
			  fwrite("\0", sizeof(char), 1, desw); 
			  fwrite((char *) &len, sizeof(char), 1, desw);
			}
		    }
		  e=(char *)MIN;

		  if (len<5+offset) 
		    {
		      len++; 
		      tail=len<<3;
		      total[len]=0x80;
		      mov2++;
		      if (ender)
			memcpy(mov2, end, len_end);
		      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		      refresh();
#else
                      fflush(stdout);
#endif
		      fwrite("\0", sizeof(char), 1, desw); 
		      fwrite((char *) &len, sizeof(char), 1, desw);
		    }
		}
              d=(char *)MIN;

	      if (len<6+offset) 
		{
		  len++;
		  tail=len<<3;
		  total[len]=0x80;
		  mov2++;
		  if (ender)
		    memcpy(mov2, end, len_end);
		  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
		  refresh();
#else
                  fflush(stdout);
#endif
		  fwrite("\0", sizeof(char), 1, desw); 
		  fwrite((char *) &len, sizeof(char), 1, desw);
		}
	    }
          c=(char *)MIN;

	  if (len<7+offset) 
	    {
	      len++; 
	      tail=len<<3;
	      total[len]=0x80;
	      mov2++;
	      if (ender)
		memcpy(mov2, end, len_end);
	      printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	      refresh();
#else
              fflush(stdout);
#endif
	      fwrite("\0", sizeof(char), 1, desw); 
	      fwrite((char *) &len, sizeof(char), 1, desw);
	    }
	}
      b=(char *)MIN;

      if (len<8+offset)
	{
	  len++; 
	  tail=len<<3;
	  total[len]=0x80;
	  mov2++;
	  if (ender)
	    memcpy(mov2, end, len_end);
	  printw("\nPassword size: %u \n", len);
#ifdef NCURSES
	  refresh();
#else
          fflush(stdout);
#endif
	  fwrite("\0", sizeof(char), 1, desw); 
	  fwrite((char *) &len, sizeof(char), 1, desw);
	}
    }
  
  return(0);
}








/* Crack from file */
/*
  OK
*/


int crack4_read_core3(input, resume)
     char *input;
     char *resume;
{
  char conv[]="0123456789abcdef";
  char *copy;
  char *mov;
  char digest[16];
  unsigned int i;
  struct timeval *tp;
  float doff;
  char hash[16];
  register char *bufferr;
  register char *bufferr2;
  char bufferr3[256];
  register unsigned int amount;
  register unsigned int max,z=0;
  unsigned char length[2]={'1','\n'};
  char flag;
  unsigned char byte1, byte2, byte3, byte4;

  tp=(struct timeval *)malloc(sizeof(struct timeval)); 
  bzero(digest, 16);
  mov=digest;
  copy=input;
  strncpy(target, input, 32);
  

  up2low(input);
  ascii2bin(copy, conv, mov);
  Decode(digest2, mov, 16);  
  
    

   
  total=(char *)malloc(57);
  if (!total)
    {
      mdmesg(7, NULL);
      doexit();
    }

  bufferr=(char *)malloc(BLOCKSIZE*1024*1024);
  if (!bufferr)
    {
      mdmesg(7, NULL);
      doexit();
    }
  
  
  
  mdmesg(26, BLOCKSIZE);
  
  if (fastwrite)
    mdmesg(23, NULL);
  else
    mdmesg(24, NULL);
  
  mdmesg(25, NULL);
  fflush(desw);

#ifndef ISBIG_ENDIAN  
  setvbuf(desw, NULL, _IONBF, 0);
#endif

  mdmesg(22, BLOCKSIZE);
  
  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;
  
  amount=fread(bufferr, sizeof(char), BLOCKSIZE*1024*1024, desw);
  
  gettimeofday(tp, NULL);
  elapsed=tp->tv_sec-start;
  elapsed_u=tp->tv_usec-start_u;

  if (elapsed_u < 0)
    {
      elapsed_u=1000000+elapsed_u;
      if (elapsed>0) elapsed--;
    }
  doff=(float)elapsed+((float) elapsed_u/(float)1000000);
  doff=((float) (amount/(1024*1024)) /doff);
  
  printw(" %.1f MB/sec.\n", doff);
  
#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif


  fseek(desw, 0, SEEK_SET);
  
  signal(SIGINT, handle);

  if (benchmode)
    {
      alarm(duration);
      signal(SIGALRM, handle);
    }
  
  
  fread(&flag, sizeof(char), 1, desw);
  if (fastwrite != (unsigned int)flag-48)
    {
      mdmesg(13, NULL);
      doexit();
    }
  
  
  
  gettimeofday(tp, NULL);
  start=tp->tv_sec;
  start_u=tp->tv_usec;
  
  
  
#ifdef NCURSES
  while((mvwprintw(stdscr, 14+z, 0, "Mounting 1 new block in memory ... ")==OK)&&((amount=fread(bufferr, sizeof(char), BLOCKSIZE*1024*1024, desw)))&&(mvwprintw(stdscr, 14+z++, 37, "done")==OK))
    {
#else
      while((write(1, "\nMounting 1 new block in memory ... ", 36))&&((amount=fread(bufferr, sizeof(char), BLOCKSIZE*1024*1024, desw)))&&(write(1, " done\n", 6)))
	{
#endif
	  
	  bufferr2=bufferr;
	  max=(unsigned int)bufferr+amount;
	  
	  while((unsigned int)bufferr2+len+16 < max)
	    {      
	      
	      
	      if (*bufferr2 == '\0')
		{
		  len= (unsigned char)*(bufferr2+1);
		  bufferr2+=2;
		  
#ifdef NCURSES
		  mvwprintw(stdscr, 14+z++, 0, "Password size: %u", len);
		  refresh();
#else
		  write(1,"\nPassword size: ", 16);
		  printf("%u", len);
		  fflush(stdout);
#endif
		}
	      
	      if (!fastwrite)
		{
		  test=(unsigned char *)(bufferr2+len+1);
		  
#ifdef NCURSES
		  if (verbosity)
		    {
		      mvwprintw(stdscr, 10, 25, "%s", bufferr2);
		      mvwprintw(stdscr, 10, 59, " <--  precomputed string.");
		      if (verbosity==2)
			{
			
			  mvwprintw(stdscr, 11, 25, "%s", test);
			  mvwprintw(stdscr, 11, 59, " <--  precomputed hash.");
			  attrset(COLOR_PAIR(1)|A_BOLD);
			  mvwprintw(stdscr, 12, 25, "%s", target);
			  mvwprintw(stdscr, 12, 59, " <--  reference.");
			  attrset(COLOR_PAIR(1));
			  mvwprintw(stdscr, 13, 59, " ");
			}
		      refresh();
		    }
#else
		  if (verbosity)
		    {
		      printw("\n%s <--  precomputed string", bufferr2);
		      if (verbosity==2)
			{
			  printw("\n%s <--  precomputed hash", test);
			  printw("\n%s <--  reference\n", target);
			}
		      fflush(stdout);
		    }
#endif

		  ascii2bin(test, conv, hash);
		  Decode(result2, hash, 16);
		  bufferr2+=len+35;
		}
	      else

		{
		 
		  result2[0]=*((unsigned int *)(bufferr2+len));
		  result2[1]=*((unsigned int *)(bufferr2+len+4));
		  result2[2]=*((unsigned int *)(bufferr2+len+8));
		  result2[3]=*((unsigned int *)(bufferr2+len+12));
		  
		  bufferr2+=len+16;





#ifdef NCURSES
		  if (verbosity)
		    {
		      strncpy(bufferr3, bufferr2-len-16, len);
		      bufferr3[len]='\0';
		      strcpy(total, bufferr3);
		      mvwprintw(stdscr, 10, 25, "%s", total);
		      mvwprintw(stdscr, 10, 59, " <--  precomputed string.");
		      
		      
		      if (verbosity==2)
			{
			  for (i=0; i<4; i++)
			    {
			      byte1=(unsigned char) ((result2[i])>>24);
			      byte2=(unsigned char) ((result2[i]&0x00ff0000)>>16);
			      byte3=(unsigned char) ((result2[i]&0x0000ff00)>>8);
			      byte4=(unsigned char) ((result2[i])&0x000000ff);
			      
			      mvwprintw(stdscr, 11, 25+(8*i), "%02x%02x%02x%02x", byte4, byte3, byte2, byte1);
			    }
			  mvwprintw(stdscr, 11, 59, " <--  precomputed hash.");
			  
			 
			  
			  attrset(COLOR_PAIR(1)|A_BOLD);
			  mvwprintw(stdscr, 12, 25, "%s", target);
			  mvwprintw(stdscr, 12, 59, " <--  reference.");
			  attrset(COLOR_PAIR(1));
			  mvwprintw(stdscr, 13, 59, " ");
			}
		      refresh();
		    }
#else
		  if (verbosity)
		    {
		      strncpy(bufferr3, bufferr2-len-16, len);
		      bufferr3[len]='\0';
		      printw("\n%s <--  precomputed string\n", bufferr3);
		      if (verbosity==2)
			{		  
			  for (i=0; i<4; i++)
			    {
			      byte1=(unsigned char) ((result2[i])>>24);
			      byte2=(unsigned char) ((result2[i]&0x00ff0000)>>16);
			      byte3=(unsigned char) ((result2[i]&0x0000ff00)>>8);
			      byte4=(unsigned char) ((result2[i])&0x000000ff);
			      
			      printw("%02x%02x%02x%02x",byte4, byte3, byte2, byte1);
			    }
			  printw(" <--  precomputed hash");
			  printw("\n%s <--  reference\n", target);
			}
		    }
#endif	  


		}
	    
	      
	  count++;
	  if ((*digest2==*result2)&&(*(digest2+1)==*(result2+1))&&(*(digest2+2)==*(result2+2))&&(*(digest2+3)==*(result2+3)))
	    { 
	      if (fastwrite)
		strncpy(total, bufferr2-len-16, len);
	      else
		strcpy(total, (char *)((unsigned int)bufferr2-len-35));
	      if (!stats(total, len))
		mdmesg(8, NULL);
	      
	      
	      if (!all)
		{
		  fclose(desw);
		  return(1);
		}                        
	    }                  
	    }
      if (fastwrite)
	fseek(desw,((unsigned int)bufferr2-max), SEEK_CUR);
      else
	fseek(desw,((unsigned int)bufferr2-max), SEEK_CUR); 
	}
  
  printw(" No more byte to read\n");
  
#ifdef NCURSES
  refresh();
#else
  fflush(stdout);
#endif
  
  return(0);
}
  
  

 void core43(void)
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
  DNGG (b, c, d, a, tail, S24, SS24, b1, c1, d1, a1);             /* 28 */
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
  DNHH (b, c, d, a, tail, S34, SS34, b1, c1, d1, a1);            /* 40 */
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






 int core43bis(void)
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


  if (!fast)
    {
      fasta = working[0];
      fastb = working[1];
      fastc = working[2];
      fastd = working[3];
      
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 47 */ 
      fastc -= x1[7];
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 46 */
      fastd -= x1[11];    
      RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 45 */
      fasta -= x1[3];
      RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 44 */
      fastb -= x1[13];
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 43 */
      fastc -= x1[5];
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 42 */
      fastd -= x1[9];
      RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 41 */
      fasta -= x1[1];
      RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 40 */
      fastb -= tail;
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 39 */
      fastc -= x1[6];
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 38 */
      fastd -= x1[10];
      RNHH0 (fasta, fastb, fastc, fastd, S31, SS31);        /* 37 */
      fasta -= x1[2];  
      RNHH0 (fastb, fastc, fastd, fasta, S34, SS34);        /* 36 */ 
      fastb -= x1[12];
      RNHH0 (fastc, fastd, fasta, fastb, S33, SS33);        /* 35 */ 
      fastc -= x1[4];
      RNHH0 (fastd, fasta, fastb, fastc, S32, SS32);        /* 34 */ 
      fastd -= x1[8];
      fast=1;

    }


 
 if ((fasta == a) && (fastb == b) && (fastc == c) && (fastd == d))
   return 1; 
 if ((fasta == a1) && (fastb == b1) && (fastc == c1) && (fastd == d1))
   return 2;
   
 return(0);

}
