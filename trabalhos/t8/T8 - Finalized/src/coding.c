
#include <stdio.h>





void Encode (output, input, len)
unsigned char *output;
unsigned int *input;
unsigned int len;
{
  register i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
 output[j] = (unsigned char)(input[i] & 0xff);
 output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
 output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
 output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}





void Decode (output, input, len)
unsigned int *output;
unsigned char *input;
unsigned int len;
{
  register i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
 output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j+1]) << 8) |
   (((unsigned int)input[j+2]) << 16) | (((unsigned int)input[j+3]) << 24);
}














