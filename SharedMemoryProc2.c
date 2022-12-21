#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

struct shmseg{
	int sig_comp;
	int sig_rcv;
	char buffer[5][12];
};

int main(){
	sleep(3);
	int shmid;
	struct shmseg* s;
	shmid=shmget(0x1234,sizeof(struct shmseg),0644|IPC_CREAT);
	
	s=shmat(shmid,NULL,0);

	while(s->sig_comp!=1){
		for(int i=0;i<5;i++){
			for(int j=0;j<12;j++){
				if(j!=0){
					printf("%c",s->buffer[i][j]);
				}
				else{
					printf("%d",s->buffer[i][0]);
				}
			}
			printf("\n");
		}
		printf("Strings read successfully\n");
		s->sig_rcv=(int )s->buffer[4][0];
		sleep(3);
	}
	printf("Reading done successfully\n");
	return 0;
}
