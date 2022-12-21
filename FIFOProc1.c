#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>

int main() {
	struct timespec begin, end;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	int fd1;
	int ret;
	// FIFO file path
	char * myfifo1 = "/tmp/myfifo";
	
	mkfifo(myfifo1, 0666);

	char array[51][10];
	char sent[100];	

	for(int i = 1 ; i < 51 ; i++){
		char st[10] = "RaNdOm";
		char yes[5];
		sprintf(yes , "%d", i);
		strcat(st, yes);
		strcpy(array[i], st);
	}

	int last = 1;
	char got[5];
	
	while(last < 50) {
		fd1 = open(myfifo1, O_WRONLY);
		strcat(array[last], "\n");
		for(int j = last + 1 ; j <= last + 4 ; j++){
			strcat(array[last] , array[j]);
			strcat(array[last] , "\n");
		}
		printf("\nStrings sent to Process 2\n");
		strcpy(sent, array[last]);
		ret = write(fd1, sent, strlen(sent) + 1);
		close(fd1);	
		fd1 = open(myfifo1, O_RDONLY);
		read(fd1, got, sizeof(got));
		last = atoi(got);
		printf("ID received from P2 %d \n", last);
		close(fd1);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long int difference = end.tv_sec - begin.tv_sec;
	long double d = (long double)(end.tv_nsec - begin.tv_nsec)/1000000000;
	printf("Time Taken : %Lf\n", (long long unsigned int)difference + d);
	return 0;
}
