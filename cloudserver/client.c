#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "typedef.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n, i, j, messagesize;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    activeFunc functions[10];

    char buffer[32768*8];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    while(1)
    {
	fgets(buffer,255,stdin);
	n = write(sockfd,"<PARA",5);
	if (n < 0) 
	 error("ERROR writing to socket");
	messagesize = 5;

	for(j=0; j<6; j++)
	{
	    functions[j].colorMap.red = 0x24;
	    functions[j].colorMap.green = 0x24;
	    functions[j].colorMap.blue = 0x24;
	    functions[j].coordinate[0].x= 0.5;
	    functions[j].coordinate[0].y= 0;
	    functions[j].transType = 1;
	    functions[j].numActiveFuncs = 6;
	    for(i=0; i<11; i++)
	    {
		functions[j].transPara[i] = (float)i + (float)i/10;
	    }
	    functions[j].prob = 0.5;
	    n = write(sockfd,&functions[j],sizeof(functions[j]));
	    if (n < 0) 
		 error("ERROR writing to socket");
	    messagesize +=n;


	}
	n = write(sockfd,"<\\PARA",6);
	if (n < 0) 
	     error("ERROR writing to socket");
	messagesize +=n;
	n = write(sockfd,"<DATA",5);
	if (n < 0) 
	 error("ERROR writing to socket");

	messagesize +=n;
	bzero(buffer,32768*8);
	n = write(sockfd,buffer,sizeof(buffer));

	if (n < 0) 
	     error("ERROR writing to socket");

	messagesize +=n;
	n = write(sockfd,"<\\DATA",6);
	if (n < 0) 
	     error("ERROR writing to socket");
	messagesize +=n;
	printf("write %d message in total\n", messagesize);

	n = read(sockfd,buffer,255);
	if (n < 0) 
	     error("ERROR reading from socket");
	printf("%s\n",buffer);
    }
    close(sockfd);
    return 0;
}
