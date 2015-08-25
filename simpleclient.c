#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int	sockfd;
	socklen_t	len;
	struct	sockaddr_in address;
	int	result;
	char	buff[1024]="GET /index.html HTTP/1.0\r\n\r\n";


	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9999);
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if (result == -1)
	{
		perror("oops: client1");
		exit(1);
	}

	write(sockfd, buff, strlen(buff));
	memset(buff,0x00,sizeof buff);
	read(sockfd, buff, sizeof(buff)-1);

	printf("char from server = \n%s\n", buff);

	close(sockfd);
	return (0);
}


