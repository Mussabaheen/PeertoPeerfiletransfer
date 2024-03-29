#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 3490 // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; // connector’s address information

	if (argc != 3) {
		fprintf(stderr,"usage: client hostname\nOR\nProvide File Path which you want to Recieve/send?\n");
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
	int choice;

	while(1)
	{
		
	printf("Do you want to (Recieve:0)/(send:1) file? ");
		scanf("%d",&choice);
		if(choice==0 || choice==1)
			break;
	}
	their_addr.sin_family = AF_INET;     // host byte order
	their_addr.sin_port = htons(PORT); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	printf("SIZE : %d \n",strlen(argv[2]));
	choice?strcat(argv[2],"1"):strcat(argv[2],"0");
	printf("%s",argv[2]);
	send(sockfd,argv[2],strlen(argv[2]),0);
	buf[numbytes] = '\0';
	printf("Received: %s",buf);	
	close(sockfd);
	return 0;
}
