#include <omp.h>
#include <stdio.h>
#define N 10
int main()
{
  int i;
  float a[N], b[N], result;
  omp_set_num_threads(6);
  #pragma omp parallel default(none), private(i), shared(a,b)
  #pragma omp for
  for (i = 0; i < N; i++)
  {
    a[i] = (i+1) * 1.0;
    b[i] = (i+1) * 2.0;
  }
  result = 0.0;
  #pragma omp parallel default(none), private(i), shared(a,b)

  #pragma omp for
  for (i=0; i < N; i++){
    result = result + (a[i] * b[i]);
  }
  printf("Final result= %f \n",result);

  return(0);
}



