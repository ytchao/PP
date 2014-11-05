#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int thread_num;
pthread_mutex_t mutex;
long long int number_of_tosses,batch;
long long int number_in_circle=0;
time_t start,end;
double times;
void* toss()
{
  long long int sample_num=0;
  long long int i=0;
  srand(time(NULL));
  unsigned seed=rand();
  for(;i<batch;i++)
  {  
     double x,y,dis,times;
     x=((double)rand_r(&seed)/(double)RAND_MAX);
     y=((double)rand_r(&seed)/(double)RAND_MAX);
     x=x*2-1;
     y=y*2-1;
     dis=x*x+y*y;
     if(dis<=1)
     {
       sample_num++;
     }
  }
  pthread_mutex_lock(&mutex);
  number_in_circle+=sample_num;
//  time(&end);
//  times=end-start;
  pthread_mutex_unlock(&mutex); 
//  printf("thread exit:%f\n",times);
  return NULL;
}

int main(int argc,char* argv[])
{
 // start=clock();
  long thread;
  double pi;
  thread_num=get_nprocs();
  number_of_tosses=strtoll(argv[1],NULL,10);
  batch=number_of_tosses/thread_num;
  pthread_t* handler;
  handler=malloc(thread_num*sizeof(pthread_t));
 // time(&start);//time start
  pthread_mutex_init(&mutex,NULL);
  //thread create
  for(thread=0;thread<thread_num;thread++)
   pthread_create(&handler[thread],NULL,toss,NULL);
 //thrad join
  for(thread=0;thread<thread_num;thread++)
         pthread_join(handler[thread],NULL);
 
 pi=4*number_in_circle/(double)number_of_tosses;
 pthread_mutex_destroy(&mutex);
// time(&end);//time end
 free(handler);
// end=clock();
// times =end-start;
 printf("pi:%f\n",pi);
 return 0;
}

