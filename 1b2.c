#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t forks[5];
sem_t bowl;

void eat(int n){
	printf("Philosopher %d is eating now\n" , n);
}

void take_left(int n){
	printf("Philosopher %d is trying to pick left fork\n" , n);
	sem_wait(&forks[n]);
	printf("Philosopher %d picks the left fork\n" , n);
}

void take_right(int n){
	printf("Philosopher %d is trying to pick right fork\n" , n);
	sem_wait(&forks[(n + 1) % 5]);
	printf("Philosopher %d picks the right fork\n" , n);
}

void* process(void* n){
	while(1){
		int p=*(int *)n;
		int val;
		printf("Philosopher %d is thinking \n",p);
		if(p==4){
			take_right(p);
			take_left(p);
		}
		else{
			take_left(p);
			take_right(p);
		}
		sem_getvalue(&bowl,&val);
		printf("Value of bowl semaphore is %d\n",val); 
		sem_wait(&bowl);
		printf("Philosopher %d picked bowl %d\n",p,val);
		
		eat(p);
		sleep(2);

		sem_post(&bowl);
		printf("Philosopher %d released bowl %d\n",p,val);
		sem_getvalue(&bowl,&val);
		printf("Value of semaphore is %d\n",val);

		sem_post(&forks[(p+1)%5]);
		printf("Philosopher %d released fork %d\n",p,(p+1)%5);
		sem_post(&forks[p]);
		printf("Philosopher %d released fork %d\n",p,p);
		printf("Philosopher %d finished eating\n",p);
	}		
}

int main(){
	pthread_t philosophers[5];
	int a[5];
	
	sem_init(&bowl,0,2);

	for(int i=0;i<5;i++){
		sem_init(&forks[i],0,1);
	}
	for(int i=0;i<5;i++){
		a[i]=i;
		pthread_create(&philosophers[i],NULL,process,(void *)&a[i]);
	}
	for(int i=0;i<5;i++){
		pthread_join(philosophers[i],NULL);
	}
	return 0;
}
