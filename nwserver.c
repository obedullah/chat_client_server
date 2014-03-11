#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int count=0;
char text[100];
int res,i=0;
pthread_t a_thread[10];
void *thread_result;
int server_sockfd, client_sockfd;
int server_len, client_len,flag=0;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

void *server(void *arg)
{
	int *sockfd=(int *)arg;
	count++;
	while(1)
	{
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		read(*sockfd, text, 100);
		printf("the text from Client : ");
		puts(text);
		if(strcmp(text, "quit")==0)
		{	
			count--;
			write(*sockfd, "Good Bye !", 100);
			pthread_exit((void *)&sockfd);
			return;
		}
		printf("Enter message : ");
		gets(text);
		write(*sockfd, text, 100);
		printf(".................\n");
	}
}
int main()
{
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address,server_len);
	listen(server_sockfd,10);
	while(1)
	{
		printf("server waiting...\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		res = pthread_create(&a_thread[i], NULL, server, (void *)&client_sockfd);
		if (res != 0) 
		{
			perror("Thread creation failed\n");
			exit(EXIT_FAILURE);
		}
		res = pthread_join(a_thread[i], &thread_result);
		if (res != 0) 
		{
			perror("Thread join failed\n");
			exit(EXIT_FAILURE);
		}
	}
}
