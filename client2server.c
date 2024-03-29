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
#include <fcntl.h>
#define BACKLOG 10 // how many pending connections queue will hold

void sigchld_handler(int s)
{
	while(wait(NULL) > 0);
}

int main(int argc,char *argv[])
{
	int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
	char *file_read=(char*)malloc(10000000);
	int status;
	int MYPORT=atoi(argv[1]);
	int fd=open(argv[2],O_RDONLY);
	
	printf("hello hello hello");
	printf("hello hello hello");
	int buffer=read(fd,file_read,10000000);
	printf("FILE SIZE : %d \n",buffer);
	printf("PORT : %d\n",MYPORT);
	struct sockaddr_in my_addr;     // my address information
	struct sockaddr_in their_addr; // connector’s address information
	int sin_size;
	char *buf_fname=(char *)malloc(10000);
	strcpy(buf_fname,"");
	struct sigaction sa;
	int yes=1;
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
		printf("server2client waitng here......\n");
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1) {
			perror("accept");
			//continue;
		}
		printf("client2server: got connection from %s\n",
				inet_ntoa(their_addr.sin_addr));
		if (!fork()) { // this is the child process
			close(sockfd); // child doesn’t need the listener



				
	
						
		
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)		
				perror("send");	
		
				

			close(new_fd);
			exit(0);
		}
		//	char buf[100];
		
			recv(new_fd,buf_fname,10000,0);
			
			printf("RECIVED DATA INDEXES : %s \n",buf_fname);
			close(new_fd); // parent doesn’t need this
	return 0;
}

