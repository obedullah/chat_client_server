#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int sockfd;
	int len;
	char text[100];
	struct sockaddr_in address;
	int result;
	while(1)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		address.sin_port = htons(9734);
		len = sizeof(address);
		result = connect(sockfd, (struct sockaddr *)&address, len);
		if(result == -1)
		{
			perror("oops: client\n");
			exit(1);
		}
		printf("enter your message : ");
		fgets(text,100,stdin);
		write(sockfd,text,100);
		printf("...............\n");
		/*///read(sockfd,text,100);
		//printf("message from server : ");
		//puts(text);
		if(strcmp(text,"Good Bye !")==0)
		{
			exit(1);
		}*/
	}
}
