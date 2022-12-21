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
	int fd1;
	char *myfifo1 = "/tmp/myfifo";
	mkfifo(myfifo1, 0666);
	int k = 0;
	int ret;
	char buffer[100];
	char sd[10];
	while(k < 50){
		fd1 = open(myfifo1, O_RDONLY);
		ret = read(fd1, buffer, 100);
		printf("Strings received from Process 1\n %s", buffer);
		close(fd1);
		k += 5;
		char arr[5];
		sprintf(arr,"%d", k);
		strcpy(sd, arr);
		printf("Index sent back to Process 1\n");
		fd1 = open(myfifo1, O_WRONLY);
		write(fd1, sd, strlen(sd) + 1);
		close(fd1);
	}   
	return 0;
}
