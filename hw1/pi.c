#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int thread_num;
long long int number_of_tosses,batch;
long long int number_in_circle[5];

void* toss(void * bank)
{
  long mybank=(long)bank;
  long long int sample_num=0;
  long long int i=0;
  srand(time(NULL));
  unsigned seed=rand();
  long long int rMax = RAND_MAX/2;
  long long int rMaxsquare = rMax*rMax;
  long long int x,y;
  for(;i<batch;i++)
  {  
     x = rand_r(&seed)-rMax;
     y = rand_r(&seed)-rMax;
     if(x*x+y*y<=rMaxsquare)
     {
       sample_num++;
     }
  }
  number_in_circle[mybank]+=sample_num;
  return NULL;
}

int main(int argc,char* argv[])
{
  long thread;
  double pi;
  thread_num=get_nprocs();
  int i=0;
  for(;i<thread_num;i++)
     number_in_circle[i]=0;
  number_of_tosses=strtoll(argv[1],NULL,10);
  batch=number_of_tosses/thread_num;
  pthread_t* handler;
  handler=malloc(thread_num*sizeof(pthread_t));

  for(thread=0;thread<thread_num;thread++)
   pthread_create(&handler[thread],NULL,toss,(void*)thread);
 //thrad join
  for(thread=0;thread<thread_num;thread++)     
    pthread_join(handler[thread],NULL);
  i=1;
 for(;i<thread_num;i++)
   number_in_circle[0]+=number_in_circle[i];
 pi=4*number_in_circle[0]/(double)number_of_tosses;
 free(handler);
 printf("pi:%f\n",pi);
 return 0;
}

