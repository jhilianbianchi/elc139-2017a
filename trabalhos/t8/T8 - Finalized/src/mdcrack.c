/*
   MDCrack.c
   MD5/MD4/NTLM1 collision bruteforcer

   *******************************************
   derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm
   *******************************************

   Try every passwords up to 8 chars length.
   Useful to crack authentication protocols using MD5/MD4 hashed passwords.
   Use it only to choose a strong password or something like that 
   and please, nothing illegal.

   Author: Gregory Duchemin 
   Email : c3rb3r@hotmail.com 
   www : http://mdcrack.multimania.com
   www : http://mdcrack.df.ru

   Credit to Simeon Pilgrim for his fast MD5 algorithm.
   Thanks to Solar Designer for the Russian Mirror
*/




#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include "version.h"
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "global.h"

#ifndef RESUME_FILE
#define RESUME_FILE "/tmp/.mdcrack.resume"
#endif
#ifndef BENCH_HASH
#define BENCH_HASH "ffffffffffffffffffffffffffffffff"
#endif
#ifndef ALFA
#define ALFA "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUWXYZ"
#endif
#ifndef BLOCKSIZE
#define BLOCKSIZE 50
#endif


#ifndef NCURSES
#define printw printf
#endif



#define swap32(x) (((x & 0x000000ff)<<24) +\
                   ((x & 0x0000ff00)<<16) +\
                   ((x & 0x00ff0000)>>16) +\
                   ((x & 0xff000000)>>24))


void hashprint(unsigned int *);

unsigned long count;
unsigned long count2;
unsigned int verbosity=0;
unsigned int algo=1;
unsigned int benchmode=0;
unsigned int minimal=0;
unsigned int duration=0;
unsigned int custom=0;
unsigned int all=0;
unsigned int ender=0;
unsigned int beginer=0;
unsigned int hwrite=0;
unsigned int hread=0;
unsigned int fastwrite=0;
unsigned int fast=0;
unsigned int fasta, fastb, fastc, fastd;
unsigned int val=0;
unsigned int len=1, len_begin, len_end;
signed int diff;

int counter=0;
FILE *desw;


long elapsed;
long elapsed_u;
char target[33];
char *filename;
char *alfa;
char *test;
char *test2;
char *total;
char *total2;
extern int optind;
extern char *optarg;
unsigned int tail;
long start;
long start_u;
char *begin;
char *end;
char *output;
unsigned int working[4];
unsigned int result2[4], result3[4], digest2[4];


#ifdef ISBIG_ENDIAN
unsigned int x1[14];
#else
unsigned int *x1;
#endif






/* SIGINT/SIGALRM handler */


void handle()
{
 FILE *des;
 struct timeval ft;
 float sub;
 unsigned int i,j;
 struct stat *secure;
 int key;
 

 gettimeofday(&ft, NULL);
 elapsed=(ft.tv_sec)-start;
 elapsed_u=(ft.tv_usec)-start_u;

 signal(SIGINT, SIG_DFL);
 alarm(0);


 output=(char *)malloc(114);
 if (!output)
   {
     mdmesg(7, NULL);
     doexit(0);
   }

 bzero(output, 114);
 memcpy(output, total, len);


 if (algo==2)
   {
     if (beginer)
       len_begin=unicode2ascii(begin, len_begin);
     if (ender)
       len_end=unicode2ascii(end, len_end);
     len=unicode2ascii(output, len);
   }
 

#ifdef NCURSES

 if (verbosity)
   {
     if (hread)
       {   
	 attrset(COLOR_PAIR(1));
	 mvwprintw(stdscr, 10, 25, "%s", output);
	 mvwprintw(stdscr, 10, 59, " <--  precomputed string.");
	 mvwprintw(stdscr, 11, 59, "");

	 if (verbosity==2)
	   {
	     hashprintw(result2, 11, 25);
	     mvwprintw(stdscr, 11, 59, " <--  precomputed hash.");
	     attrset(COLOR_PAIR(1)|A_BOLD);
	     hashprintw(digest2, 12, 25);
	     mvwprintw(stdscr, 12, 59, " <--  reference.");
	     attrset(COLOR_PAIR(1));
	     mvwprintw(stdscr, 13, 59, "");
	   }

	 refresh();
       }
     else
       {
	 attrset(COLOR_PAIR(1));         
	 mvwprintw(stdscr, 8, 25, "%s", output);
	 mvwprintw(stdscr, 8, 59, " <-- string.");
	 mvwprintw(stdscr, 9, 59, "");
	 if (!beginer)
	   {
	     mvwprintw(stdscr, 9, 25, "%c", output[0]+diff);
	     mvwprintw(stdscr, 9, 26, "%s", &output[1]);
	     mvwprintw(stdscr, 9, 59, " <-- string.");
	   }
	 mvwprintw(stdscr, 10, 59, "");


	 if (verbosity==2)
	   {
	     if (beginer)
	       {
		 hashprintw(result2, 9, 25);
		 mvwprintw(stdscr, 9, 59, " <-- hash.");
		 attrset(COLOR_PAIR(1)|A_BOLD);
		 hashprintw(digest2, 10, 25);
		 mvwprintw(stdscr, 10, 59, " <-- reference.");
		 attrset(COLOR_PAIR(1));
		 mvwprintw(stdscr, 11, 0, "");
	       }
	     else
	       {
		 hashprintw(result2, 10, 25);
		 mvwprintw(stdscr, 10, 59, " <-- hash.");
		 hashprintw(result3, 11, 25);
		 mvwprintw(stdscr, 11, 59, " <-- hash.");
		 attrset(COLOR_PAIR(1)|A_BOLD);
		 hashprintw(digest2, 12, 25);
		 mvwprintw(stdscr, 12, 59, " <-- reference.");
		 attrset(COLOR_PAIR(1));
		 mvwprintw(stdscr, 13, 0, "");
	       }   
	   }
	 refresh();
       }
   }
 

 mdmesg(32, NULL);
 attrset(COLOR_PAIR(2));
 refresh();

#endif 
 

 if (hwrite)
   {
     mdmesg(14, filename);
     fclose(desw);
   }
 

 if (!benchmode)
   {
     secure=(struct stat*)malloc(1*sizeof(struct stat));
     if (!secure)
       {
	 mdmesg(7, NULL);
	 exit(0);
       }

     key=lstat(RESUME_FILE, secure);

     if (S_ISLNK(secure->st_mode))
       mdmesg(15, NULL);
     else
       {
	 des=fopen(RESUME_FILE, "w+");
	 chmod(RESUME_FILE, S_IRUSR);
         mdmesg(46, NULL);

	 if (des)
	   {
	     if ((!hwrite) && (!hread)) 
	       strcpy(filename, "none");
	     
	     fprintf(des, "%s %s %d %d %s %d %d %s %d %d %d", target, output, verbosity, custom, alfa+1, hwrite, hread, filename, fastwrite, beginer, ender);
	  
	     if (!beginer)
	       fprintf(des, " none");
	     else
	       fprintf(des, " %s", begin);

	     if (!ender)
	       fprintf(des, " none");
	     else
	       fprintf(des, " %s", end);

             fprintf(des, " %d", algo);
	     
	     fclose(des);
	   }
	 printw("\nResume file "RESUME_FILE" generated.\n");
       } 
   }

 
 if ((elapsed_u<10000) && (!elapsed))
   {     
     if (benchmode)
       printw("\nBenchmark result."); 
     
     printw("\n");
     for (i=0; i<40; i++)
       {
	 
#ifdef NCURSES 
	 if (((i<14)||(i>25))&& (i!=11)&&(i!=28))
	   attrset(COLOR_PAIR(1));
	 else
	   attrset(COLOR_PAIR(1)|A_BOLD);
#endif
	 
	 printw(SYMBOL);
       }

     printw("\n");     
     printw("Current string --> ");
     
#ifdef NCURSES 
     attrset(COLOR_PAIR(1)|A_REVERSE);
     refresh();
#endif
     
     printw("%s\n", output);
     
#ifdef NCURSES 
     attrset(COLOR_PAIR(2));
     refresh();
#endif
     
     
#ifdef NCURSES 
     attrset(COLOR_PAIR(2)|A_REVERSE);
     refresh();
#endif
     printw("%s\n", output); 
     mdmesg(29, NULL);
     
   }
 else
   { 
     if (elapsed_u < 0)
       {
	 elapsed_u=1000000+elapsed_u;
         if (elapsed>0) elapsed--;
       }
     
     sub=(float)elapsed+((float)elapsed_u/1000000);
     
     
     if (benchmode)
       printw("\nBenchmark result."); 


     
     if (!hread)
       {
	 printw("\n");
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
	 printw("Current string --> ");
	 
#ifdef NCURSES 
	 attrset(COLOR_PAIR(1)|A_REVERSE);
	 refresh();
#endif
	 printw("%s\n", output);
#ifdef NCURSES 
	 attrset(COLOR_PAIR(2));
	 refresh();
#endif
	 printw("Collision(s) tested : %lu in %lu second(s), %lu millisec, %lu microsec.\nAverage of %.1f hashes/sec.\n\n", count, elapsed, (elapsed_u/1000), (elapsed_u%1000),(float) ((long)count/sub));
       }
     else
       {
	 printw("\n");
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
	 printw("\nCollision(s) tested : %lu in %lu second(s), %lu millisec, %lu microsec.\nAverage of %.1f hashes/sec.\n\n", count, elapsed, (elapsed_u/1000), (elapsed_u%1000),(float) ((long)count/sub));
       }
   
   }

#ifdef NCURSES
 refresh();
#else
 fflush(stdout);
#endif
 
doexit();
}






/* Usage */



void usage(code)
     unsigned int code;
{



#ifndef NCURSES
  logow();
  
  
  printw("\" Bruteforce your hashes \"\n\nUsage: MDCrack [-h] [-r] [-v | -V] [-d] [-W file -R file -F] [-b challenge] [-e challenge] [-t secs] [-S size] [-a] [-s string] [-M MD4/MD5/NTLM1] [digest] \n-h : (h)elp, this text\n-r : (r)elease number\n-v : set (v)erbose mode\n-V : more (V)erbose\n-d : (d)elete any resume-file \n-W : file where to (W)rite all computed hashes\n-R : file where to (R)ead computed hashes\n-F : (F)ast write (Hashes file is no longer human-readable)\n-b : challenge to concatenate (b)efore passwords.\n-e : challenge to concatenate at passwords (e)nd.\n-t : Benchmark mode (t)imer, compute during secs seconds\n-S : password (S)ize, minimal size to start with\n-a : find (a)ll collisions (won't stop to the first found)\n-s : feed a custom charset (s)tring\n-M : Choose (M)D4, MD5 or NTLM1.\nNo option forces mdcrack to resume a previously stopped session\n\nAuthor: Gregory Duchemin\nEmail: c3rb3r@hotmail.com\nWWW: http://mdcrack.multimania.com \nWWW: http://mdcrack.df.ru\nCredit to Simeon Pilgrim for his fast MD5 algorithm\n\n*******************************************\n\n");
  mdmesg(code);
  
#else
  mvwprintw(stdscr, 8 , 0, "");
  printw("Usage: MDCrack [-h] [-r] [-v | -V] [-d] [-W file -R file -F] [-b challenge] [-e challenge] [-t secs] [-S size] [-a] [-s string] [-M MD4/MD5/NTLM1] [digest] \n");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-h");
  attrset(COLOR_PAIR(1));
  printw(" : (");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("h");
  attrset(COLOR_PAIR(1));
  printw(")elp, this text\n");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-r");
  attrset(COLOR_PAIR(1));
  printw(" : (");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("r");
  attrset(COLOR_PAIR(1));
  printw(")elease number\n");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-v | -V ");
 attrset(COLOR_PAIR(1));
  printw(": set (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("v");
 attrset(COLOR_PAIR(1));
  printw(")erbose mode / more (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("V");
 attrset(COLOR_PAIR(1));
  printw(")erbose\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-d");
 attrset(COLOR_PAIR(1));
  printw(" : (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("d");
 attrset(COLOR_PAIR(1));
  printw(")elete any resume-file \n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-W | -R ");
 attrset(COLOR_PAIR(1));
  printw(": file where to (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("W");
 attrset(COLOR_PAIR(1));
  printw(")rite or (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("R");
 attrset(COLOR_PAIR(1));
  printw(")ead all computed hashes\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-F");
 attrset(COLOR_PAIR(1));
  printw(" : (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("F");
 attrset(COLOR_PAIR(1));
  printw(")ast write (Hashes file is no longer human-readable)\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-b");
 attrset(COLOR_PAIR(1));
  printw(" : challenge to concatenate (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("b");
 attrset(COLOR_PAIR(1));
  printw(")efore passwords.\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-e");
 attrset(COLOR_PAIR(1));
  printw(" : challenge to concatenate at passwords (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("e");
 attrset(COLOR_PAIR(1));
  printw(")nd.\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-t");
 attrset(COLOR_PAIR(1));
  printw(" : Benchmark mode (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("t");
 attrset(COLOR_PAIR(1));
  printw(")imer, compute during secs seconds\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-S");
 attrset(COLOR_PAIR(1));
  printw(" : password (");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("S");
 attrset(COLOR_PAIR(1));
  printw(")ize, minimal size to start with\n");
 attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-a");
  attrset(COLOR_PAIR(1));
  printw(" : find (");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("a");
  attrset(COLOR_PAIR(1));
  printw(")ll collisions (won't stop to the first found)\n");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-s");
  attrset(COLOR_PAIR(1));
  printw(" : feed a custom charset (");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("s");
  attrset(COLOR_PAIR(1));
  printw(")tring\n");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("-M");
  attrset(COLOR_PAIR(1));
  printw(" : choose (");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("M");
  attrset(COLOR_PAIR(1));
  printw(")D4, MD5 or NTLM1");

  printw("\nNo option forces mdcrack to resume a previously stopped session\nAuthor: Gregory Duchemin - ");
  attrset(COLOR_PAIR(1)|A_BOLD);
  printw("c3rb3r@hotmail.com");
 
  if (code)
    mdmesg(code, NULL);
  
  logow();
  
#endif
  
  doexit();
}





/* Resume file cleaner */



int cleanup(reference)
	char *reference;
{

   if (remove(reference))
     return(1); 
return(0);
}






/* main */


int main (argc, argv)
     int argc;
     char *argv[];
{
  int i;
  int found;
  FILE *des1;
  int c;
  char *resume;
  char value[128];
  char feed[500];
  

  bzero(value, 128);
  alfa=(char *)malloc(64);
  strcpy(alfa+1, ALFA);
  *alfa='\0';


#ifdef NCURSES

 initscr();
 cbreak();
 noecho();
 start_color();
 clear();
 nodelay(stdscr, TRUE);
 
 init_pair(1, COLOR_GREEN, COLOR_BLACK);
 init_pair(2, COLOR_WHITE, COLOR_BLACK);
 init_pair(3, COLOR_RED, COLOR_BLACK);
 init_pair(4, COLOR_YELLOW, COLOR_BLACK);
 init_pair(5, COLOR_BLACK, COLOR_BLACK);	
 init_pair(6, COLOR_BLUE, COLOR_BLACK);
 attrset(COLOR_PAIR(1) | A_BOLD);


 scrollok(stdscr, TRUE);      
 syncok(stdscr, TRUE);
 leaveok(stdscr, TRUE);

#endif



 mdmesg(33, NULL);
 
 resume=(char *)malloc(200*sizeof(char));
 if (!resume)
   {
     mdmesg(7, NULL);
     doexit(0);
   }
 bzero(resume, 200);
 begin=(char *)malloc(256);
 if (!begin)
   {
     mdmesg(7, NULL);
     doexit();
   }
 bzero(begin, 256);
 end=(char *)malloc(256);
 if (!end)
   {
     mdmesg(7, NULL);
     doexit();
   }
 bzero(end, 256);
 filename=(char *) malloc(512);
 if (!filename)
   {
     mdmesg(7, NULL);
     doexit();
   }




 
 if (argc==1) 
   {
     if ((des1=fopen(RESUME_FILE, "r")) == NULL )
       {
	 usage(2);
	 doexit(); 
       }
     
   
   

     fscanf(des1, "%s %s %d %d %s %d %d %s %d %d %d %s %s %d", value, resume, &verbosity, &custom, alfa+1, &hwrite, &hread, filename, &fastwrite, &beginer, &ender, begin, end, &algo);
     *(alfa)=0x00;

   
     
     mdmesg(16, NULL); 
     printw("       { \n         Hash: \"%s\"\n         Last try: \"%s\"\n         Verbosity: %d\n         Read: %d\n         Write: %d\n         File: %s\n         Fastmode: %d\n         Charset: %s\n         Begining string: %s\n         Ending string: %s\n         Algorithm: %d\n       }\n\n", value, resume, verbosity, hread, hwrite, filename, fastwrite, alfa+1, begin, end, algo);

     if (!strcmp("none", begin)) 
       *begin='\0';
     if (!strcmp("none", end)) 
       *end='\0';
     
#ifdef NCURSES
     refresh(); 
#else
     fflush(stdout); 
#endif



     if (hwrite)
       {
	 desw=fopen(filename, "a");
	 if (!desw)
	   {
	     usage(3);
	     doexit(); 
	   }
       }
     if (hread)
       {
	 desw=fopen(filename, "r");
	 if (!desw)
	   {
	     usage(4);
	     doexit(); 
	   }
       }
     sleep(2);



#ifdef NCURSES
     for (i=4;i<20;i++)
       mvwprintw(stdscr, i, 0,"                                                                                                                                                                                                                                       ");

     mvwprintw(stdscr, 3, 0, " ");


     refresh();
#endif
     
       
     
   }
 else
   {
     
     while(1)
       {
	 c=getopt(argc, argv, "hrvVdaFs:t:b:e:W:R:M:S:");
	 if (c==-1)
	   break;
	 
	 switch(c)
	   {
	   case 't':
	     benchmode=1;
	     duration=atoi(optarg); 
	     break;
	     
	   case 'S':
	     minimal=atoi(optarg);
	     if ((minimal <1) || (minimal>8))
	       minimal=0;
	     break;

	   case 'h':
	     usage(0); 
	     doexit();
	     break;
	     
	   case 'r':
	     printw("\n\n");
	     doexit3();
	     break;
 
	   case 'd':
	     if (cleanup(RESUME_FILE)) 
	       {
		 usage(5);
		 doexit();
	       }
	     else
	       {
		 mdmesg(17, NULL);
		 doexit();
	       }
	     break;
	     
	   case 'v':
	     if (!verbosity)
	       verbosity=1;
	     break;
	     
	   case 'V':
	     verbosity=2;
	     break;
	     
	   case 'b':
	     if ((strlen(optarg)+strlen(end)+9)>56)
	       {
		 mdmesg(34, NULL);
		 doexit();
	       }     
#ifdef ISBIG_ENDIAN 
	     begin=(char *)malloc(strlen(optarg)+1);
#else
	     realloc(begin, strlen(optarg)+1); 
#endif
	     if (!begin)
	       {
		 mdmesg(7, NULL);
		 doexit();
	       }
	     strcpy(begin, optarg);
	     beginer=1;
	     break;
	     
	   case 'e':
	     if ((strlen(begin)+strlen(optarg)+9)>56)
	       {
		 mdmesg(34, NULL);
		 doexit();
	       }
#ifdef ISBIG_ENDIAN      
	     end=(char *)malloc(strlen(optarg)+1);
#else
	     realloc(end, strlen(optarg)+1);
#endif
	     
	     if (!end)
	       {
		 mdmesg(7, NULL);
		 doexit();
	       }
	     strcpy(end, optarg);
	     ender=1;
	     break;
	     
	   case 'a':
	     all=1;
	     break;
	     
	   case 's':
	     custom=1;
	     charset_sort(optarg);
	     
#ifdef ISBIG_ENDIAN
	     alfa=(char *)malloc(strlen(optarg)+2);  
#else
	     realloc(alfa, strlen(optarg)+2);
#endif

	     strcpy(alfa+1, optarg); 
	     *(alfa)='\0';
	     break;


	   case 'M':
	     if (!strcmp("MD4", optarg)) algo=0;
	     if (!strcmp("NTLM1", optarg)) algo=2;
	     break;

	     
	   case 'W':
	     if (hread)
	       {
		 usage(9);
		 doexit(); 
	       }
	     if ((desw=fopen(optarg, "w+")) == NULL)
	       {
		 usage(10);
		 doexit(); 
	       }
	     strcpy(filename, optarg);
	     hwrite=1;
	     break;
	     
	     
	   case 'R':
	     if (hwrite)
	       {
		 usage(9);
		 doexit(); 
	       }
	     
	     if ((desw=fopen(optarg, "r")) == NULL )
	       {
		 usage(6);
		 mdmesg(6, NULL);
		 doexit(); 
	       }
	     strcpy(filename, optarg);
	     hread=1;
	     break;
	     
	     
	   case 'F':
	     fastwrite=1;
	     break;
	     
	   case '?':
	     usage(0);
	     doexit();
	     break;
	     
	   default:
	     usage(0);
	     break;
	   }
       }
   }
 
 
 if ((optind+1<=argc) || (argc==1) || (benchmode))
   {
     
     if (argc==1)
       strcpy(feed, value);
     else
       {
	 if (benchmode)
	   strcpy(feed, BENCH_HASH);
	 else
	   strcpy(feed, *(argv+optind));
       }
     
    

     if (strlen(feed) != 32)
       {
	 mdmesg(1, NULL); 
	 doexit();
       }
     
     
     if (custom) 
       mdmesg(18, alfa+1);
     else if (!hread)
       mdmesg(19, alfa+1);
     
     
     if (hread)
       {
	 switch(algo)
	   {
	   case '\02':
	     doexit();
	     break;

	   case '\01':
	     if (!(found=crack_read_core3(feed, resume)))
	       mdmesg(0, NULL);
	     break;

	   case '\00':
	     if (!(found=crack4_read_core3(feed, resume)))
	       mdmesg(0, NULL);
	   }	    
	 doexit();
       }
     
     

     if (verbosity)
       {
	
	 switch(algo) 
	   {

	   case '\02':
	     if (beginer)
	       {
		 mdmesg(45, NULL);
		 if (!(found=crack_verbose_NTLM_core3b(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 mdmesg(45, NULL);
		 if (!(found=crack_verbose_NTLM_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }

	     break;
	     
	   case '\01':
	     if (beginer)
	       {
		 mdmesg(39, NULL);
		 if (!(found=crack_begin_verbose_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 mdmesg(39, NULL);
		 if (!(found=crack_verbose_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }	     
	     break;
	     
	   case '\00':
	     if (beginer)
	       {
		 mdmesg(43, NULL);
		 if (!(found=crack4_begin_verbose_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 mdmesg(43, NULL);
		 if (!(found=crack4_verbose_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     break;

	   default:
	     break;
	   }
	 doexit();
       }
     


     if (hwrite)
       {

	 switch(algo)
	   {

	   case '\02':
	     doexit();
	     break;

	   case '\01':
	     if (beginer)
	       {
		 if (!(found=crack_begin_write_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 if (!(found=crack_write_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     break;

	   case '\00':
	     if (beginer)
	       {
		 if (!(found=crack4_begin_write_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 if (!(found=crack4_write_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     break;
	     
	     doexit();
	   }
       }
 

     if (algo==2)
       {
	 if (beginer)
	   {
	     mdmesg(44, NULL);
	     if (!(found=crack_NTLM_core3b(feed, resume)))
	       mdmesg(0, NULL);
	   }
	 else
	   {
	     mdmesg(44, NULL);
	     if (!(found=crack_NTLM_core3(feed, resume)))
	       mdmesg(0, NULL);
	   }
	 doexit();
       }


     if ((strlen(begin)+strlen(end)+9)>28)
       {
	 
	 if (beginer)
	   {
	     if (algo)
	       {
		 mdmesg(38, NULL);
		 if (!(found=crack_begin_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 mdmesg(42, NULL);
		 if (!(found=crack4_begin_core3(feed, resume)))
		   mdmesg(0, NULL);
	       }

	   }
	 else
	   if (algo)
	     { 
	       mdmesg(38, NULL);
	       if (!(found=crack_core3(feed, resume)))
		 mdmesg(0, NULL);
	     }
	   else
	     {
	       mdmesg(42, NULL);
	       if (!(found=crack4_core3(feed, resume)))
		 mdmesg(0, NULL);
	     }
	 doexit();
       }
     

      if ((strlen(begin)+strlen(end)+9)>12)
       {
	 if (beginer)
	   {
	     if (algo)
	       {
		 mdmesg(37, NULL);
		 if (!(found=crack_begin_core2(feed, resume)))
		   mdmesg(0, NULL);
	       }
	     else
	       {
		 mdmesg(41, NULL);
		 if (!(found=crack4_begin_core2(feed, resume)))
		   mdmesg(0, NULL);
	       }
	   }
	 else
	   if (algo)
	     {
	       mdmesg(37, NULL);
	       if (!(found=crack_core2(feed, resume)))
		 mdmesg(0, NULL);
	     }
	   else
	     {
	       mdmesg(41, NULL);
	       if (!(found=crack4_core2(feed, resume)))
		 mdmesg(0, NULL);
	     }
	 doexit();
       }
      


      if (beginer)
	{
	  
	  if (ender)
	    {
	      if (algo)
		{
		  mdmesg(36, NULL);
		  if (!(found=crack_begin_end_core1(feed, resume)))
		    mdmesg(0, NULL);
		}
	      else
		{
		  mdmesg(40, NULL);
		  if (!(found=crack4_begin_end_core1(feed, resume)))
		    mdmesg(0, NULL);
		}
	    }
	  else
	    if (algo)
	      {
		mdmesg(36, NULL);
		if (!(found=crack_begin_core1(feed, resume)))
		  mdmesg(0, NULL);
	      }
	    else
	      {
		mdmesg(40, NULL);
		if (!(found=crack4_begin_core1(feed, resume)))
		  mdmesg(0, NULL);
	      }

	  doexit();
	}
      

     if (ender)
       {
	 if (algo)
	   {
	     mdmesg(36, NULL);
	     if (!(found=crack_end_core1(feed, resume)))
	       mdmesg(0, NULL);
	   }
	 else
	   {
	     mdmesg(40, NULL);
	     if (!(found=crack4_end_core1(feed, resume)))
	       mdmesg(0, NULL);
	   }  
	 doexit();
       }


     
     if (algo)
       {
	 mdmesg(36, NULL);
	 if (!(found=crack_core1(feed, resume)))
	   mdmesg(0, NULL);
       }
     else
       {
	 mdmesg(40, NULL);
	 if (!(found=crack4_core1(feed, resume)))
	   mdmesg(0, NULL);
       }
     
     doexit();
   }
 
 usage(0);
 doexit();
}






/* ncursized exit */


doexit()
{

#ifdef NCURSES
  attrset(COLOR_PAIR(2));
  mdmesg(30, NULL);
  attrset(COLOR_PAIR(2)|A_BLINK);
  
  mdmesg(35, NULL);
  nodelay(stdscr, FALSE);
  refresh();
  cbreak();
  noecho();
  getch();
  endwin();
#endif
  
  exit(0);
  
}

doexit2()
{

#ifdef NCURSES  
  refresh();
  cbreak();
  noecho();
  getch();
  endwin();
#endif
  
  exit(0);
  
}



doexit3()
{

#ifdef NCURSES
  attrset(COLOR_PAIR(2));
  mdmesg(30, NULL);
  attrset(COLOR_PAIR(2)|A_BLINK);
  mdmesg(35, NULL);
  nodelay(stdscr, FALSE);
  refresh();
  cbreak();
  noecho();
  getch();
  endwin();
#endif

  exit(0);  
}









































