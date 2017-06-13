#include <stdio.h>
#include <unistd.h>
#include "global.h"


unsigned int unicode2ascii(char *input, int size)
{
  int i, size_final;
  char *tempo;

  tempo=(char *)malloc((size+1)*sizeof(char));
  if (!tempo)
    return(0);
  bzero(tempo, size+1);

  for (i=0; i<(size/2); i++)
      *(tempo+i)=*(input+(i*2));
      
  *(tempo+i)='\0';
  size_final=size/2;

 
  bzero(input, (size_final+1));
  memcpy(input, tempo, size_final);
  free(tempo);

  return(size_final);
}


unsigned int ascii2unicode(char *input)
{
  int i, size;
  char *tempo;

  tempo=(char *)malloc((strlen(input)*2+1)*sizeof(char));
  if (!tempo)
    return(0);
  bzero(tempo, (strlen(input)*2+1));

  for (i=0; i<strlen(input);i++)
    {
      *(tempo+(i*2))=*(input+i);
      *(tempo+(i*2)+1)='\0';
    }
  size=i*2;
  realloc(input, (size+1)*sizeof(char));
  if (!input)
    return(0);
  bzero(input, (size+1));
  memcpy(input, tempo, (size));
  free(tempo);
  return(size);
}

