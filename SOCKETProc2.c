#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "blah.socket"

int main(int argc, char *argv[]) {
	struct sockaddr_un serv;
	int down_flag = 0;
	int connection_socket;
	int ret;
	int max = 0;
	int data_socket;
	char buff[12];

	connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	memset(&serv, 0, sizeof(serv));
	serv.sun_family = AF_UNIX;
	strncpy(serv.sun_path, SOCKET_NAME, sizeof(serv.sun_path) - 1);

	ret = bind(connection_socket, (const struct sockaddr *) &serv, sizeof(serv));
	ret = listen(connection_socket, 100);

	while(1) {
		data_socket = accept(connection_socket, NULL, NULL);
		max = 0;
		int current = max;
		while(1) {
			ret = read(data_socket, buff, sizeof(buff));
			buff[sizeof(buff) - 1] = 0;
			current = buff[0];

			printf("String sent back by Client: ");		
			
			for(int i = 1; i < 11; i++) {
				printf("%c", buff[i]);
			}
			printf("\n");
			
			sprintf(buff, "%d", current);
			printf("ID sent back by Client = %s\n", buff);		

			if(current == max + 5) {
				max = current;
				ret = write(data_socket, buff, sizeof(buff));
			}	
			if(current >= 50) break;
		}
		close(data_socket);
	}
	return 0;
}
