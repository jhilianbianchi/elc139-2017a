#include <stdlib.h>
#include <stdio.h>

unsigned long long int fatorial (unsigned long long int n)
{
   
   if(n==1)
       return n;
   return (fatorial(n-1) * n);
}

int main(int argc, char **argv)
{
   unsigned long long int result;
   int repeat, i = 0, in;
   if ((argc != 3)) {
      exit(EXIT_FAILURE);
   }
   in = atoi(argv[1]);       // numero a calcular fatorial
   repeat = atoi(argv[2]);  // numero de repeticoes(forçar mais tempo de cálculo)
   while (i < repeat)
   {
        result = fatorial(in);
	i++;
   }
   printf("O fatorial de %d eh :%llu\n", in, result);
   return 0;
}


