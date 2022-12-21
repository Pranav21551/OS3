#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

sem_t forks[5];

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
	printf("Philosopher %d is thinking\n",p);
	if(p==4){
		take_right(p);
		take_left(p);
	}
	else{
		take_left(p);
		take_right(p);
	}
	eat(p);
	sleep(2);
	printf("Philosopher %d has finished eating\n" , p);
	sem_post(&forks[p]);
	printf("Philosopher %d released fork %d\n",p,p);

	sem_post(&forks[(p+1)%5]);
	printf("Philosopher %d released fork %d\n",p,(p+1)%5);

	printf("Philoopher %d finished eating\n",p);
	}
}

int main(){
	int a[5];
	pthread_t philosophers[5];

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
}
