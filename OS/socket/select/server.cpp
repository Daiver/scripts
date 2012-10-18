
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>


void ClientServ(int fd)//serving client
{
	char ch;
	read(fd, &ch, 1);						
	printf("serving client on fd %d\n", fd);
	ch+=2;
	write(fd, &ch, 1);
}

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	sockaddr_in server_address;
	sockaddr_in client_address;
	int result;
	fd_set readfds, testfds;
	///* Создаем серверный сокет:
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	///* Создаем очредь для запросов и набор readfds для соединений с сокетом server_sockfd:
	listen(server_sockfd, 5);
	FD_ZERO(&readfds);
	FD_SET(server_sockfd, &readfds);
	///* Ожидаем запросы на соединение: 
	while(1) {
		//char ch;
		int fd;
		int nread;
		testfds = readfds;
		printf("server waiting\n");
		result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *) 0);
		if(result < 1) {			
			perror("server5");
			exit(1);
		}
		printf("Find activity...\n");
		for(fd = 0; fd < FD_SETSIZE; fd++) {
			if(FD_ISSET(fd,&testfds)) {
				
				if(fd == server_sockfd) {
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd, (sockaddr *)&client_address, (socklen_t*)&client_len);
					FD_SET(client_sockfd, &readfds);
					printf("adding client on fd %d\n", client_sockfd);

				}

				else {
					ioctl(fd, FIONREAD, &nread);
					if(nread == 0) {
						close(fd);
						FD_CLR(fd, &readfds);
						printf("removing client on fd %d\n", fd);
					}
					else {
						ClientServ(fd);
					/*
						read(fd, &ch, 1);						
						printf("serving client on fd %d\n", fd);
						ch++;
						write(fd, &ch, 1);
					*/
					}
				}
			}
		}
	}
}

