#include<pthread.h>
#include<stdio.h>

#define MAXBUFF 1000

//shared Data
struct
{
	pthread_mutex_t _mutex;
	int buff[MAXBUFF];
	int nval;
	int nindex;
}sharedData = {PTHREAD_MUTEX_INITIALIZER};


void* Producer(void *arg)
{

	pthread_mutex_lock(&sharedData._mutex);
	if (sharedData.nindex >= MAXBUFF)
	{
		pthread_mutex_unlock(&sharedData._mutex);
		return NULL ;
	}

	sharedData.buff[sharedData.nindex] = sharedData.nval;
	printf("Produced: %d\n",sharedData.nval);
	sharedData.nindex += 1;
	sharedData.nval += 1;
	pthread_mutex_unlock(&sharedData._mutex);
}


void consumer_wait(int val)
{
	while(1)
	{
		pthread_mutex_lock(&sharedData._mutex);
		if (val < sharedData.nindex)
		{
			pthread_mutex_unlock(&sharedData._mutex);
			return;
		}
		pthread_mutex_unlock(&sharedData._mutex);
	}

}


void* Consumer(void *arg)
{
	int i =0;
	for(i =0;i<sharedData.nindex;i++)
	{
		consumer_wait(i);
		if(sharedData.buff[i] == i)
			printf("Consumed:  buff[%d] = %d\n",i,sharedData.buff[i]);
	}
	return NULL;
}


int main(void)
{

	pthread_t pid[4];
	pthread_t consumer;
	int i;
	for(i = 0;i<4;i++)
	{
		pthread_create(&pid[i],NULL,&Producer,NULL);
	}
	pthread_create(&consumer,NULL,&Consumer,NULL);
	int j;
	for(j = 0;j<4;j++)
	{
		pthread_join(pid[j],NULL);
	}
	pthread_join(consumer,NULL);
return 0;
}
