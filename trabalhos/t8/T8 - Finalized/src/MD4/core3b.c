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


void core43b();




/* passwords <= 56 bytes (end/begin) */
/* 
   OK 
*/


int crack4_begin_core3(input, resume)
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
      if (ender)
	strncpy(mov2, end, len_end); 
      len += offset;
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
firsttime:     			  *test=*h;
				 
				  
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif

				  core43b();       
                                  count++;
				 
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






/* Crack verbosely all size simple/file (end/begin) */
/* OK */





int crack4_begin_verbose_core3(input, resume)
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
  register unsigned int len_begin=0, len_end=0;
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
     mov=test+len_begin+len;
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


    
      mov=test+len;
      len += offset;
      memcpy(mov, end, len_end);
    }




  if (offset+9>56)
    {
      mdmesg(11, NULL);
      doexit();
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
			      for(;h<(char *)MAX;h++)
				{
firsttime:	      		  *test=*h;
							  
				 			 
				  total[len]=0x80;
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif

                                  core43b();
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

				  
				  }
				  else 
				  { 
				    char new;

				  fwrite(total, sizeof(char), len, desw);
				  fwrite(result2, sizeof(unsigned int), 4, desw);

				
				  }
                                
#ifdef NCURSES

				  mvwprintw(stdscr, 8, 25, "%s", total);
				  mvwprintw(stdscr, 8, 59, " <-- string.");
				
#else
				  printw("\n%s <-- string.", total);
				
                                
#endif
				  if (verbosity==2)
				  {
#ifdef NCURSES
				    hashprintw(result2, 9, 25);
				    mvwprintw(stdscr, 9, 59, " <-- hash.");
				   
				  
				  
				    attrset(COLOR_PAIR(1)|A_BOLD);
				    hashprintw(digest2, 10, 25);
				    mvwprintw(stdscr, 10, 59, " <-- reference.");
				   
				    attrset(COLOR_PAIR(1));
#else
				    printf("\n");
				    hashprint(result2);
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
				
                                  count++;
				 
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
				 
				}
                              h=(char *)MIN;
			      if (len<2+offset) 
				{
				   len++;
				   mov++;
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
	   memcpy(mov, end, len_end);
	   if (hwrite){
	     fwrite("\0", sizeof(char), 1, desw); 
	     fwrite((char *) &len, sizeof(char), 1, desw);}
	   tail=len<<3;
	}
    }

  return(0);

}




/* crack to file */
/*
  OK
*/


int crack4_begin_write_core3(input, resume)
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


 if (resume[0])
    {
     
     if (ender)  
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



  fflush(NULL);
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
			      for(;h<(char *)MAX;h++)
				{
firsttime:     			  *test=*h;
						 

				  total[len]=0x80;
#ifdef ISBIG_ENDIAN
				  Decode(x1, total, 56);
#endif
                                  core43b();
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

				    
				    }
				  else 
				    { 
				      char new;

				      fwrite(total, sizeof(char), len, desw);
				      fwrite(result2, sizeof(unsigned int), 4, desw);
				      
				    
				    }
				  
                                  count++;
				  
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

				
				}
                              h=(char *)MIN;
			      
			      if (len<2+offset)
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





 void core43b(void)
{
  register unsigned int a;
  register unsigned int	b;
  register unsigned int	c;
  register unsigned int	d;

  a = 0x67452301;
  b = 0xefcdab89;
  c = 0x98badcfe;
  d = 0x10325476; 
  
 
  NFF (a, b, c, d, x1[0], S11, SS11);       /* 1  */
  NFF (d, a, b, c, x1[1], S12, SS12);       /* 2  */
  NFF (c, d, a, b, x1[2], S13, SS13);       /* 3  */
  NFF (b, c, d, a, x1[3], S14, SS14);       /* 4  */
  NFF (a, b, c, d, x1[4], S11, SS11);       /* 5  */
  NFF (d, a, b, c, x1[5], S12, SS12);       /* 6  */
  NFF (c, d, a, b, x1[6], S13, SS13);       /* 7  */
  NFF (b, c, d, a, x1[7], S14, SS14);       /* 8  */
  NFF (a, b, c, d, x1[8], S11, SS11);       /* 9  */
  NFF (d, a, b, c, x1[9], S12, SS12);       /* 10 */
  NFF (c, d, a, b, x1[10], S13, SS13);      /* 11 */
  NFF (b, c, d, a, x1[11], S14, SS14);      /* 12 */
  NFF (a, b, c, d, x1[12], S11, SS11);      /* 13 */
  NFF (d, a, b, c, x1[13],S12, SS12);       /* 14 */
  NFF (c, d, a, b, tail, S13, SS13);        /* 15 */
  NFF0 (b, c, d, a, S14, SS14);             /* 16 */
  


  /*

    Round 2

  */

  
  NGG (a, b, c, d, x1[0], S21, SS21);       /* 17 */
  NGG (d, a, b, c, x1[4], S22, SS22);       /* 18 */
  NGG (c, d, a, b,x1[8], S23, SS23);        /* 19 */
  NGG (b, c, d, a, x1[12], S24, SS24);      /* 20 */
  NGG (a, b, c, d, x1[1], S21, SS21);       /* 21 */
  NGG (d, a, b, c, x1[5], S22, SS22);       /* 22 */
  NGG (c, d, a, b, x1[9],S23, SS23);        /* 23 */
  NGG (b, c, d, a, x1[13],S24, SS24);       /* 24 */
  NGG (a, b, c, d, x1[2], S21, SS21);       /* 25 */
  NGG (d, a, b, c,x1[6], S22, SS22);        /* 26 */
  NGG (c, d, a, b, x1[10],S23, SS23);       /* 27 */
  NGG (b, c, d, a, tail, S24, SS24);        /* 28 */
  NGG (a, b, c, d, x1[3], S21, SS21);       /* 29 */
  NGG (d, a, b, c, x1[7],S22, SS22);        /* 30 */
  NGG (c, d, a, b, x1[11], S23, SS23);      /* 31 */
  NGG0 (b, c, d, a, S24, SS24);             /* 32 */
  
 

  /*

    Round 3

  */

  NHH (a, b, c, d, x1[0], S31, SS31);      /* 33 */
  NHH (d, a, b, c, x1[8],S32, SS32);       /* 34 */
  NHH (c, d, a, b, x1[4], S33, SS33);      /* 35 */
  NHH (b, c, d, a, x1[12], S34, SS34);     /* 36 */
  NHH (a, b, c, d, x1[2], S31, SS31);      /* 37 */
  NHH (d, a, b, c,x1[10], S32, SS32);      /* 38 */
  NHH (c, d, a, b, x1[6],S33, SS33);       /* 39 */
  NHH (b, c, d, a, tail, S34, SS34);       /* 40 */
  NHH (a, b, c, d, x1[1], S31, SS31);      /* 41 */
  NHH (d, a, b, c,x1[9], S32, SS32);       /* 42 */
  NHH (c, d, a, b,x1[5], S33, SS33);       /* 43 */
  NHH (b, c, d, a,x1[13], S34, SS34);      /* 44 */
  NHH (a, b, c, d, x1[3],S31, SS31);       /* 45 */
  NHH (d, a, b, c,x1[11], S32, SS32);      /* 46 */
  NHH (c, d, a, b, x1[7],S33, SS33);       /* 47 */ 
  NHH0 (b, c, d, a, S34, SS34);            /* 48 */ 
 
  

  a  += 0x67452301;
  b  += 0xefcdab89;
  c  += 0x98badcfe;
  d  += 0x10325476;

 result2[0] = a;
 result2[1] = b;
 result2[2] = c; 
 result2[3] = d;
}





