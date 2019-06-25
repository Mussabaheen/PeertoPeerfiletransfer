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
	char **port_server=(char **)malloc(1000);
	int port_index=0;
	int file_index=0;
	for(int a=0;a<1000;a++)
	{
		port_server[a]=(char*)malloc(10000);
	}
	char **file_server=(char **)malloc(1000);
        for(int a=0;a<1000;a++)
        {
                file_server[a]=(char*)malloc(10000);
        }
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
	bzero(&(my_addr.sin_zero), 8);// zero the rest of the struct
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
			int index_filefound=strlen(buf_fname);
			printf("bit : %c \n",buf_fname[index_filefound-1]);
			if(buf_fname[index_filefound-1]=='0')
			{
			printf("GOT HERE! \n");	
			int torrent_bool[100];
			buf_fname[strlen(buf_fname)-1]='\0';
				int fd_file=open(buf_fname,O_RDONLY);
                //      if(fd_file==-1)
                //      {
                //              continue;
                //      }
                        char *buf_read=(char*)malloc(10000000);
                        int file_size=read(fd_file,buf_read,10000000);
				printf("FILE SIZE : %d \n",file_size);
				for(int a=0;a<100;a++)
				{
					torrent_bool[a]=1;
				}
				for(int a=0;a<port_index;a++)
				{
					torrent_bool[a]=strcmp(buf_fname,file_server[a]);
				}
				char *buf_rev=(char*)malloc(10000);
				char *buf_files=(char*)malloc(1000);
				sprintf(buf_files,"%d",file_size);
				strcpy(buf_rev,"127.0.0.1 ");
				strcat(buf_rev,buf_files);
				strcat(buf_rev," ");
				 char *argv2[100];
				argv2[0] = "cd";
                                        argv2[1] = "127.0.0.1";
				for(int a=0;a<port_index;a++)
				{
					if(torrent_bool[a]==0)
					{
						strcat(buf_rev,port_server[a]);
						strcat(buf_rev," ");
					//	printf("client download: %s \n",buf_rev);
					

                                        argv2[a+2] = file_server[port_index-1];
                                         argv2[a+3]=NULL;
					}
				}
				//system(buf_rev);
				printf("COMMAND : %s \n",buf_rev);
				int pid=fork();
			
				if(pid==0)
				{
					execvp("./cd1",argv2);
				return 0;
				}
				strcpy(buf_rev,"");
			}
			else
			{
				buf_fname[strlen(buf_fname)-1]='\0';
				sprintf(port_server[port_index],"%d",their_addr.sin_port);
				strcpy(file_server[file_index],buf_fname);			
				port_index++;
				file_index++;
			

			perror("OPEN : ");
			for(int a=0;a<100000;a++)
			{
				buf_fname[a]=' ';
			}
			strcpy(new_server,"");
			close(new_fd); // parent doesn’t need this
			//for(int a=0;a<port_index;a++)
		//	{
		//		printf("PORT FILE : %s %s \n",file_server[a],port_server[a]);
		//	
		//	}
			strcat(new_server,port_server[port_index-1]);
			strcat(new_server," ");

			strcat(new_server,file_server[port_index-1]);
			printf("COMMAND_EXECUTED %s \n",new_server);
			char *argv1[4];
			argv1[0] = "c2s";
			argv1[1] = port_server[port_index-1];
			argv1[2] = file_server[port_index-1];
			argv1[3]=NULL;
			 int pid_1=fork();
			if(pid_1==0)
			{
			//	system(new_server);
				execvp("./c2s",argv1);
				return 0;
			}
			
			strcpy(new_server,"");
			}
		}
	return 0;
}

