#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
	char  *buf=(char *)malloc(sizeof(char)*1000000000);
	
	int fd=open("torrentfile.png",O_RDONLY);
	int fd_1=open("newcreated_file.png",O_CREAT|O_WRONLY);
	int bytesread=read(fd,buf,1000000000);
	int byteswrite=write(fd_1,buf,bytesread);
	printf("Bytes Read: %d \n",bytesread);
	printf("DATA: \n %s \n",buf);
}
