#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

pthread_mutex_t forks[5];

void forkinv(int p){
	pthread_mutex_lock(&forks[p]);
	printf("Philosopher %d picked up fork %d\n",p + 1,p);
	pthread_mutex_lock(&forks[(p+1)%5]);
	printf("Philosopher %d picked up fork %d\n",p + 1,(p+1)%5);
}

void forkk(int p){
	pthread_mutex_lock(&forks[(p+1)%5]);
	printf("Philosopher %d picked up fork %d\n",p + 1,(p+1)%5);
	pthread_mutex_lock(&forks[p]);
	printf("Philosopher %d picked up fork %d\n",p + 1,p);
}

void release(int p){
	pthread_mutex_unlock(&forks[p]);
	printf("Philosopher %d released fork %d\n",p + 1,p);
	pthread_mutex_unlock(&forks[(p+1)%5]);
	printf("Philosopher %d released fork %d\n",p + 1,(p+1)%5);
}

void* process(void* n){
	while(1){
	int p=*(int *)n;
	printf("Philosopher %d is thinking\n",p + 1);
	if(p==4){
		forkinv(p);
	}
	else{
		forkk(p);
	}
	printf("Philosopher %d is eating.....\n",p + 1);
	sleep(2);
	release(p);	
	printf("Philosopher %d finished eating\n",p + 1);
	}
}

int main(){
	int k;int a[5];
	pthread_t philosophers[5];
	for(int i=0;i<5;i++){
		k=pthread_mutex_init(&forks[i],NULL);
	}
	for(int i=0;i<5;i++){
		a[i]=i;
		pthread_create(&philosophers[i],NULL,process,(void* )&a[i]);
	}
	for(int i=0;i<5;i++){
		pthread_join(philosophers[i],NULL);
	}
	for(int i=0;i<5;i++){
		pthread_mutex_destroy(&forks[i]);
	}
	return 0;
}
