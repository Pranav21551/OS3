#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

#define SOCKET_NAME "blah.socket"

int main(int argc, char* argv[]) {
	struct sockaddr_un address;
	int ret, data_socket;
	char buff[10];

	//Creating data socket
	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	memset(&address, 0, sizeof(address));

	//For local connections
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, SOCKET_NAME, sizeof(address.sun_path) - 1);
	ret = connect(data_socket, (const struct sockaddr *) &address, sizeof(address));

	//Writing data
	char randstrs[51][12] = {{0}};
	
	srand(time(NULL));
                            
    	for (int j = 0; j <= 50; j++) {
        	randstrs[j][0] = j;
    	}
  	  
    	for(int i = 0; i <= 50; i++) {
		for(int j = 1; j <= 10; j++) {
			randstrs[i][j] = rand() % 26 + 65;
		}
	}
	
	for(int i = 1; i <= 50; i++) {
		for(int j = 0; j < 12; j++) {
			if(j == 0) {
				printf("%d ", randstrs[i][j]);
			}
			else printf("%c", randstrs[i][j]);
		}
		printf("\n");
	}

	int lastIdx = 1;
	while(1) {
		printf("Sending Strings from index %d to %d\n", lastIdx, lastIdx + 4);
		for(int i = lastIdx; i < lastIdx + 5; i++) {
			ret = write(data_socket, randstrs[i], strlen(randstrs[i]) + 1);
		}

		ret = read(data_socket, buff, sizeof(buff));
		buff[sizeof(buff) - 1] = 0;
		int finalIdx = atoi(buff);
			
		printf("Maximum ID sent back by server = %s\n\n", buff);
		if(finalIdx == 50) {
			printf("Successfully sent all Strings\n");
			close(data_socket);
			exit(EXIT_SUCCESS);
			break;
		}
		else {
			lastIdx = finalIdx + 1;
		}
	}
}
