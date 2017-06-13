/*


mesgs.c
MDcrack message system


 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "version.h"

#define MSG_NUMBER 47 

#ifndef NCURSES
#define printw printf
#endif


void mdmesg(unsigned int, void *);


#ifndef RESUME_FILE
#define RESUME_FILE "/tmp/.mdcrack.resume"
#endif

char msgs[MSG_NUMBER][256]={\
"\n<<Warning>> Did not succeed to crack your hash, sorry.\n",\
"\n<<Error>> A md5 digest must have 16 bytes length (32 ascii digits from 0 to F).\n\n",\
"\n<<Error>> No resume file found.\n\n",\
"\n<<Error>> Output file could not be created.\n\n",\
"\n<<Error>> Input file could not be open.\n\n",\
"\n<<Error>> \""RESUME_FILE"\" not found.\n\n",\
"\n<<Error>> Could not open input file.\n\n",\
"\n<<Error>> Unable to allocate enough memory.\n\n",\
"\n<<Warning>> Problem while generating statistics.\n",\
"\n<<Error>> -W and -R are not compatible.\n\n",\
"\n<<Error>> Output file could not be created.\n\n",\
"\n<<Error>> Total password length can not exceed 56 chars.\n\n",\
"\n<<Warning>> Session stopped in less than 10 ms,\n<<Warning>> not enough for a statistical report.\n\n",\
"\n<<Error>> Hashes file format incompatibility (check the -F option).\n\n",\
"\n<<System>> Output Hashes file \"%s\" is now closed.\n",\
"\n<<Security>> \""RESUME_FILE"\" is already a symlink\n<<Security>> no resume file created, operation too hazardous.\n",\
"\n<<System>> \""RESUME_FILE"\" file exists ... resuming last session\n",\
"\n<<System>> Previous resume file \""RESUME_FILE"\" deleted.\n",\
"\n<<System>> Using custom charset : %s \n",\
"\n<<System>> Using default charset : %s \n",\
"\n<<System>> @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n<<System>> Disk test: write average speed (write %d MB) ... ",\
"\n<<System>> Setting system disk cache to %d MB.\n",\
"\n<<System>> @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n<<System>> Disk test: read average speed (with %d MB) ... ",\
"\n<<System>> Fastmode is activated.",\
"\n<<System>> Fastmode is disabled.",\
"\n<<System>> Disabling system disk cache.",\
"\n<<System>> File bufferization in %d MB sized block(s).",\
"\n<<System>> Sorting custom charset ... ",\
"\n<<Warning>> New charset created",\
"\n<<Warning>> Session was killed in less than 10 ms,\n<<Warning>> not enough for a statistical report.\n\n",\
"\n<<System>> Session terminated -- ",\
"\n<<Error>> Invalid MD5 digest.\n\n",\
"\n<<Warning>> Session interrupted by user.\n",\
"\n<<System>> "NAME" v"RELEASE" is starting.",\
"\n<<Error>> Total password length (including randomizers) can not exceed 55 chars.\n\n",\
"Press a key\n",\
"<<System>> Max pass size = 12 >> Entering MD5 Core 1.\n",\
"<<System>> Max pass size = 28 >> Entering MD5 Core 2.\n",\
"<<System>> Max pass size = 56 >> Entering MD5 Core 3.\n",\
"<<System>> Max pass size = 56 (verbose mode) >> Entering MD5 Core 3.\n",\
"<<System>> Max pass size = 12 >> Entering MD4 Core 1.\n",\
"<<System>> Max pass size = 28 >> Entering MD4 Core 2.\n",\
"<<System>> Max pass size = 56 >> Entering MD4 Core 3.\n",\
"<<System>> Max pass size = 56 (verbose mode) >> Entering MD4 Core 3.\n",\
"<<System>> Max pass size = 56 >> Entering NTLM1 Core.\n",\
"<<System>> Max pass size = 56 (verbose mode) >> Entering NTLM1 Core.\n",\
"\n<<Security>> \""RESUME_FILE"\" permissions changed.\n",\
};









void mdmesg(number, arg)
     unsigned int number;
     void *arg;
{
  char ident;

  if (number < MSG_NUMBER)
  {

#ifdef NCURSES

 attrset(COLOR_PAIR(2));

    ident=msgs[number][4];
    switch(ident)
      {
      case 'a':
	attrset(COLOR_PAIR(4));
	break;
      case 'e':
	attrset(COLOR_PAIR(4));
	break;
      case 'y':
	attrset(COLOR_PAIR(2));
	break;
      case 'r':
	attrset(COLOR_PAIR(3));
	break;
      }
#endif

    printw(msgs[number], arg);

#ifdef NCURSES
    refresh();
#endif

    fflush(stdout);
  }

#ifdef NCURSES
  attrset(COLOR_PAIR(1));
#endif

}











