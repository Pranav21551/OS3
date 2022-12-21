#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct shmseg{
	int sig_comp;
	int sig_rcv;
	char buffer[5][12];
};

char str[50][12]={{0}};

int main(){
	int shmid;
	struct shmseg* s;
	shmid = shmget(0x1234,sizeof(struct shmseg),0644|IPC_CREAT);
	s = shmat(shmid,NULL,0);
	char c[] = "ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvwxyz";
	for(int i = 0;i<=50;i++){
		str[i][0]=i;
	}
	for(int i = 1 ; i <= 50 ; i++){
		for(int j=1;j<=10;j++){
			str[i][j]=c[rand()%51];
		}
	}
	int a=0,t=1;
	while(1){
		for(int i=0;i<5;i++){
			for(int j=0;j<12;j++){
				s->buffer[i][j]=str[t][j];
			}
			t++;
		}
		s->sig_comp=0;
		printf("Sending strings from the index %d to %d in shared memory\n",a+1,a+5);
		sleep(3);
		printf("Id received back: %d\n",s->sig_rcv);
		printf("\n");
		a+=5;
		if(s->sig_rcv==50){
			break;
		}
	}
	printf("All Strings sent and id received successfully\n");
	s->sig_comp=1;
	return 0;
}
