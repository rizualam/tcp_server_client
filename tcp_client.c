#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;

	if(argc<3)
	{
		printf("error in argc\n");
		exit(1);
	}
        portno = atoi(argv[2]);
	sockfd= socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("error in sockfd\n");
	}
	server = gethostbyname(argv[1]);
	if(server==NULL)
	{
		printf("error in server\n");
		exit(2);
	}
	bzero((char*)&serv_addr,sizeof(serv_addr));
	
	
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port= htons(portno);

	if (connect(sockfd,&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error in connect\n");
	}
	printf("please enter\n");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n=write(sockfd,buffer,strlen(buffer));
	if(n<0)
	{
		printf("error\n");
	}
	bzero(buffer,256);
	n=read(sockfd,buffer,255);
	if(n<0)
	{
		printf("error\n");
	}
	printf("%s\n",buffer);
	if(buffer=="yes")
	{
	
	FILE *fp;
	fp=fopen("recive_file.txt","ab");
	if(fp==NULL)
	{
		printf("error opening file\n");
		return 1;
	}
	while((n=read(sockfd,buffer,255))>0)
	{
		printf("received %d\n",n);
		fwrite(buffer,1,n,fp);		
	}
	if(n<0)
	{
		printf("error\n");
	}
	}
	
return 0;

}		
