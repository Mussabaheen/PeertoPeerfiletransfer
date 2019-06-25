#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXDATASIZE 100 // max number of bytes we can get at once

int main(int argc, char *argv[])
{
	
	int status;
	int sockfd, numbytes;
	char *buf=(char*)malloc(1000000);
	char *data_file=(char*)malloc(100);
	strcpy(data_file,"Mussabaheen");
	struct hostent *he;
	struct sockaddr_in their_addr; // connector’s address information
	int ports_number=argc-3;
	float file_size=atoi(argv[2]);

	float file_div=file_size/ports_number;
	printf("VALUE : %f \n",file_div);
	float size_port=file_size - ((ports_number-1)*(int)file_div);
	printf("FILE SIZES LAST : %f %d \n",size_port,(int)file_div);
	int port[argc-3];
	for(int a=0;a<argc-3;a++)
	{
		port[a]=atoi(argv[a+3]);
		int pid=fork();
		if(pid>0)
		{
			wait(&status);
			printf("DONE! %d \n",a);
			if(a==3)
			{
				printf("DATA FILE: %s \n",data_file);	
			}
		
		}
	else
	{
	if (argc < 3) {
		fprintf(stderr,"usage: client hostname\nOR\nPORT NOT PROVIDED\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL) {
		perror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	their_addr.sin_family = AF_INET;     // host byte order
	their_addr.sin_port = htons(port[a]); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	char *buf=(char*)malloc((int)size_port);
	if ((numbytes=recv(sockfd, buf, (int)size_port, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("Received: %s",buf);	
	close(sockfd);
	return 0;
	}
	}
}

