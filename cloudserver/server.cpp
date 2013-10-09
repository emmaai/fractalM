/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include <pthread.h>
#include "rwsockthread.h"
#include "transfmimg.h"
#include "typedef.h"

pthread_mutex_t mutex;
extern volatile bool sockClose;
extern volatile unsigned long imageTargetSize;
extern volatile bool imageTargetReady;
extern unsigned char imageBufferTarget[3*1024*1024];
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd,  portno, pid, rs, buffersize, n;
     struct hostent *server;
     struct sockaddr_in serv_addr;
     pthread_t thread_rw, thread_cpt;
     threadData threadArg;

     if (argc < 3) {
         fprintf(stderr,"usage %s hostname port\n", argv[0]);
         exit(1);
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

    buffersize = 32768*8;
    pthread_mutex_init(&mutex, NULL);
     while(1)
     {
	 threadArg.socketID = sockfd;
	 threadArg.message = new unsigned char[buffersize];
	 threadArg.messageSize = buffersize;
	 rs = pthread_create(&thread_rw, NULL, rSocket, (void *)&threadArg);
	 if(rs)
	 {
		error("ERROR on creating thread_rw");
	 }
	 printf("create another thread \n");
	 pthread_mutex_lock(&mutex);
	 sockClose = false;
	 pthread_mutex_unlock(&mutex);

	 rs = pthread_create(&thread_cpt, NULL, transfmImage, (void *)&threadArg);
	 if(rs)
	 {
		error("ERROR on creating thread_cpt");
	 }

	while(1)
	{
	    if(imageTargetReady)
	    {
		printf("write image to client %d\n", imageTargetSize);
		n = write(sockfd, "<DATA", 5);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket\n");
		    break;
		}
		n = write(sockfd,imageBufferTarget,imageTargetSize);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket\n");
		    break;
		}
		n = write(sockfd, "<\\DATA", 6);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket\n");
		    break;
		}
		pthread_mutex_lock(&mutex);
		imageTargetReady = false;
		pthread_mutex_unlock(&mutex);
	    }
	    if(sockClose)
		break;
	
	}
	 pthread_join(thread_rw, NULL);
	 printf("closed by the client, thread_rw ending\n");
	 close(sockfd);
	 pthread_join(thread_cpt, NULL);

    }//end of while
     close(sockfd);
     printf("close the server socket\n");
     pthread_exit(NULL);
     return 0; /* we never get here */
}
