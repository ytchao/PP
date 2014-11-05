#include<stdlib.h>
#include "omp.h"

void main()
{
  #pragma omp parallel
  {
     int ID = omp_get_thread_num();
     printf("Hello from thread%d\n",ID);
  }
}
