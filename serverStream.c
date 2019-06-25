#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include<fcntl.h>
#define MYPORT 3490 // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold

void sigchld_handler(int s)
{
	while(wait(NULL) > 0);
}

int main(void)
{
	int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
	int status;
	struct sockaddr_in my_addr;     // my address information
	struct sockaddr_in their_addr; // connector’s address information
	int sin_size;

	struct sigaction sa;
	int yes=1;
	char *new_port=(char*)malloc(100);
	char *new_server=(char *)malloc(10000);

	strcpy(new_server,"./c2s ");
	printf("NEW STRING : %s \n",new_server);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	my_addr.sin_family = AF_INET;  // host byte order
	my_addr.sin_port = htons(MYPORT); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	bzero(&(my_addr.sin_zero), 8);
	// zero the rest of the struct
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
	while(1) { // main accept() loop
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n",
				inet_ntoa(their_addr.sin_addr));
		if (!fork()) { // this is the child process
			close(sockfd); // child doesn’t need the listener



				
	
						
		
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)		
				perror("send");	
		
			

			close(new_fd);
			exit(0);
		}
		//	char buf[100];
			char *buf_fname=(char *)malloc(100000);
			strcpy(new_port,"");
			sprintf(new_port,"%d",their_addr.sin_port);
			strcat(new_server,new_port);
			printf("PORT NUMBER : %s \n",new_server);	
			
			strcpy(buf_fname,"");	

			recv(new_fd,buf_fname,100000,0);
			printf("Recived Data : %s Length: %d  \n",buf_fname,strlen(buf_fname));
			if(buf_fname[strlen(buf_fname-1)]=='0')
			{
			}
			else
			{
				
			}
			buf_fname[strlen(buf_fname)-1]='\0';
			int fd=open(buf_fname,O_RDONLY);
			perror("OPEN : ");
			for(int a=0;a<100000;a++)
			{
				buf_fname[a]=' ';
			}
			strcpy(new_server,"");
			strcpy(new_server,"./c2s ");
			close(new_fd); // parent doesn’t need this
	}
	return 0;
}

