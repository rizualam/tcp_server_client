#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, client;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if(argc<2)
	{
		printf("error in argc\n");
		exit(1);
	}

	sockfd= socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("error in sockfd\n");
	}
	bzero((char*)&serv_addr,sizeof(serv_addr));
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port= htons(portno);

	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
	{
		printf("error in bind\n");
		exit(1);
	}
	listen(sockfd,5);
	client=sizeof(cli_addr);
	newsockfd=accept(sockfd,(struct sockaddr *) &cli_addr, &client);
	if(newsockfd<0)
	{
		printf("error in sock fd\n");
		exit(1);
	}
	bzero(buffer,256);
	n=read(newsockfd,buffer,255);
	if(n=0)
	{
		printf("error in read\n");
		exit(1);
	}
	printf("messsage:%s\n",buffer);
     /*	n= write(newsockfd,"yes",4);
	if(n<0)
	{
		printf("error");
	}*/
	while(1)
	{
		FILE *fp = fopen(buffer,"rb");
		if(fp==NULL)
		{
			printf("error file not found\n");
			n= write(newsockfd,"no",3);
			if(n<0)
			{
				printf("error\n");
			}
			return 1;
		}
		n= write(newsockfd,"yes",4);
		if(n<0)
		{
			printf("error");
		}
		while(1)
		{
			unsigned char buff[256]={0};
			n=fread(buff,1,256,fp);
			if(n>0)
			{
				printf("sending\n");
				write(newsockfd,buff,n);
			}
			if(n<256)
			{
				if(feof(fp))
				{
					printf("end of file\n");
				}
				if(ferror(fp))
				{
					printf("error reading\n");
				}
			break;
			}
			
		}
	}
	close(newsockfd);	
return 0;
}
