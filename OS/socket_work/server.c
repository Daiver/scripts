#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

char cha = 'A';

void ClientWork(int client_sockfd)
{
	char ch;
	printf("Shell request...\n");
	read(client_sockfd, &ch, 1);
	write(client_sockfd, &cha, 1);
	close(client_sockfd);
}

int main()
{
	cha--;
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 5);
	
	printf("server waiting\n");
	while(1) {
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		cha++;	
		int chid = fork();
		if (!chid) {
			ClientWork(client_sockfd);
			return;	
		}
	}
}

