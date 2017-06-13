
/*

  hash.c

  hash oriented functions


*/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef NCURSES
#include <ncurses.h>
#endif

#ifndef NCURSES
#define printw printf
#endif



int ascii2bin(copy, conv, mov)
     char *copy;
     char *conv;
     char *mov;
{
  register int i,j,k;
  for (i=0;i<32;i+=2)
    {
      j=0;
      while ((conv[j]!=(*copy)) && (j<16)) j++;
      k=0;
      while ((conv[k]!=(*(copy+1))) && (k<16)) k++;
      if ((j==16) || (k==16))
	{
	  mdmesg(31, NULL);
	  doexit();
	}
      *mov=(char) ((j<<4) & 0xf0);
      *mov=(*mov)| (char) (k & 0x0f);
      copy+=2;
      mov++;
    }
  return(1);
}



int up2low(input)
     char *input;
{
  register int i;
  for (i=0; i<32; i++)
    if ((*(input+i) >= 65) && (*(input+i) <= 70))
        *(input+i)=*(input+i)+32;
  return(1);
}



void hashprint (digest)
unsigned int digest[4];
{
  int i;
  unsigned char byte1, byte2, byte3, byte4;

 for (i=0; i<4; i++)
 {
	 byte1=(unsigned char) ((digest[i])>>24);
	 byte2=(unsigned char) ((digest[i]&0x00ff0000)>>16);
	 byte3=(unsigned char) ((digest[i]&0x0000ff00)>>8);
	 byte4=(unsigned char) ((digest[i])&0x000000ff);
  
	 printf ("%02x%02x%02x%02x", byte4, byte3, byte2, byte1);
 }
}





void hashprintw (digest, y, x)
unsigned int digest[4];
unsigned int y;
unsigned int x;
{
  int i;
  unsigned char byte1, byte2, byte3, byte4;

 for (i=0; i<4; i++)
 {
         byte1=(unsigned char) ((digest[i])>>24);
         byte2=(unsigned char) ((digest[i]&0x00ff0000)>>16);
         byte3=(unsigned char) ((digest[i]&0x0000ff00)>>8);
         byte4=(unsigned char) ((digest[i])&0x000000ff);
#ifdef NCURSES
         mvwprintw (stdscr, y, x+(i*8), "%02x%02x%02x%02x", byte4, byte3, byte2, byte1);
#endif
 }
}
