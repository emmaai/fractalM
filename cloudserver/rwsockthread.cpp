#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <map>
#include "rwsockthread.h"
#include "typedef.h"

extern activeFunc functionPara[PARAMNUMBER];
extern unsigned char *imageBufferSource;
char paramBuffer[1*PARAMNUMBER*sizeof(activeFunc)];
unsigned long bufferPtr = (unsigned long)imageBufferSource;
unsigned long paraPtr = (unsigned long)paramBuffer;
volatile unsigned long paramCounter = 0;
volatile bool imageSourceReady = false;
volatile bool imageTargetReady = false;
volatile bool sockClose = false;
volatile bool generateHR;
extern pthread_mutex_t mutex;


void *rSocket (void *threadarg)
{
   int n, sock, buffersize, i, j, bodySize, headSize;
   unsigned short cmd = 0;
   unsigned short status = 0;
   unsigned long bodyPtr;
   threadData *threadArg;
   unsigned char *buffer;
   threadArg = (threadData *)threadarg;
   sock = threadArg->socketID;
   buffer = threadArg->message;
   buffersize = threadArg->messageSize;
   printf("socket id is %d\n", sock);
    while(1)
    {
       printf("begin read\n");
       bzero(buffer,buffersize);
	n = read(sock,buffer,buffersize);
       printf("read size is %d\n", n);
	if (n==0) 
       {
	    pthread_mutex_lock(&mutex);
	    sockClose = true;
	    pthread_mutex_unlock(&mutex);
	    printf("nothing to read closed?\n");
	    break;
	}
       if (n < 0)
       {
	    pthread_mutex_lock(&mutex);
	    sockClose = true;
	    pthread_mutex_unlock(&mutex);
	    printf("ERROR reading from socket %d\n", n); 
	    break;
       }

	/* cmd has 4 status
	*   0: received all message body, expect new message head
	*   1 << 0: expect more message body of "COMD"
	*   1 << 1: expect more message body of "PARA"
	*   1 << 2: expect more message body of "DATA"
	*/
		    
	status = parsCmd((unsigned long)buffer, n, cmd);	
	cmd = status;
	printf("last command is %d\n", cmd);

	//test code here
	
       
    }
    printf("exit the thread rwSocket\n");
    pthread_exit(NULL);
}

void *wSocket(void *threadarg)
{
}

int parsCmd(unsigned long buffer, int buffersize, short cmd)
{
    char *headPtr, *tailPtr, *bodyPtr;
    short status = 0;
    short lastCmd = cmd;
    int bodySize = 0;
    int n = buffersize;
    headPtr = (char *)buffer;
    bodyPtr = (char *)buffer;
    tailPtr = (char *)buffer;

    //tailPtr = (char *)memchr(headPtr, '<', n);
    /*
    printf("tailPtr is %d\n", (unsigned long)tailPtr);
    tailPtr = (char *)(bodyPtr, n, "<PARA", 5); 
    printf("tailPtr is %d\n", (unsigned long)tailPtr);
    */
    if(cmd == (1<<1))
	status |= (1<<2);
    if(cmd == (1<<2))
	status |= (1<<4); 
    while(tailPtr)
    {
	switch(status)
	{
	    case 0:
		if(tailPtr = (char *)memmem(headPtr, n, "<COMD" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("head found %s\n", bodyPtr);
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    status |= (1<<0);
		    lastCmd |= (1<<0);
		    break;
		}else if(tailPtr = (char *)memmem(headPtr, n, "<PARA" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("head found %s\n", tailPtr);
		    printf("bodyPtr is %lu\n", (unsigned long)bodyPtr);
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    status |= (1<<2);
		    lastCmd |= (1<<1);
		    break;
		}else if(tailPtr=(char*)memmem(headPtr,n, "<DATA" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("<DATA head found\n");
		    status |= (1<<4);
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    lastCmd |= (1<<2);
		    break;
		}else if(tailPtr = (char *)memmem(headPtr, n, "<\\COMD", 6))
		{
		    bodySize= tailPtr-bodyPtr;
		    printf("tail found %s\n", tailPtr);	
		    if(!strncmp(bodyPtr, "HR", 2))
		    {
			printf("generate hr volume\n"); 
			pthread_mutex_lock(&mutex);
			generateHR = true;
			pthread_mutex_unlock(&mutex);
		    }
		    status |= (1<<1);
		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    lastCmd &= ~(1<<0);
		    break;
		}else if(tailPtr=(char *)memmem(headPtr, n, "<\\PARA", 6))
		{
		    bodySize = tailPtr-bodyPtr;
		    printf("tail found %s\n", tailPtr);	
		    memcpy((char *)paraPtr, bodyPtr, bodySize);
		    memcpy((char *)functionPara, paramBuffer, PARAMNUMBER*sizeof(activeFunc));

		    /*
		    for(int i=0; i< 8; i++)
		    {
			printf("the function parameter %d\n", i);
			printf("functionPara numActiveFuncs: %lu\n", functionPara[i].funcNo);
			for(int j=0; j<8; j++)
			{
			    printf("functionPara coordiate: %f*%f*%f\n", functionPara[i].coordinate[j].x, 
				functionPara[i].coordinate[j].y, functionPara[i].coordinate[j].z);
			}
		    }
		    */

		    pthread_mutex_lock(&mutex);
		    paramCounter=1;
		    /*
		    if(paramCounter==3)
			paramCounter = 1;
			*/
		    printf("paramcounter is %u\n", paramCounter );
		    pthread_mutex_unlock(&mutex);
		    paraPtr = (unsigned long)paramBuffer;
		    /*
		    if(paramCounter == 2)
			paraPtr = (unsigned long)paramBuffer;
		    else
			paraPtr += PARAMNUMBER*sizeof(activeFunc);
			*/
		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    status |= (1<<3);
		    lastCmd &= ~(1<<1);
		    break;
		}else if(tailPtr = (char *)memmem(headPtr, n, "<\\DATA", 6))
		{
		    bodySize = tailPtr-bodyPtr;
		    pthread_mutex_lock(&mutex);
		    memcpy((unsigned char *)bufferPtr, (unsigned char *)bodyPtr, bodySize);
		    imageSourceReady = true;
		    pthread_mutex_unlock(&mutex);
		    bufferPtr = (unsigned long)imageBufferSource;
		    printf("<\\DATA tail found \n");	
		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    status |= (1<<5);
		    lastCmd &= ~(1<<2);
		    break;
		}
		status = 0;
		headPtr = tailPtr;
		break;
	    case (1<<0):
		if(tailPtr = (char *)memmem(headPtr, n, "<\\COMD", 6))
		{
		    bodySize = tailPtr-bodyPtr;
		    printf("tail found 2 %s\n", bodyPtr);	
		    if(!strncmp(bodyPtr, "HR", 2))
		    {
			printf("generate hr volume\n"); 
			pthread_mutex_lock(&mutex);
			generateHR = true;
			pthread_mutex_unlock(&mutex);
		    }

		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    status |= (1<<1);
		    lastCmd &= ~(1<<0);
		    break;
		}
		headPtr = tailPtr;
		break;
	    case (1<<2):
		if(tailPtr = (char *)memmem(headPtr, n, "<\\PARA", 6))
		{
		    bodySize = tailPtr-bodyPtr;
		    printf("tail found %s\n", tailPtr);	
		    printf("tailPtr is %lu\n", (unsigned long)tailPtr);
		    printf("bodysize is %d\n", bodySize);
		    printf("paraptr is %lu\n", (unsigned long)paraPtr);
		    memcpy((char *)paraPtr, bodyPtr, bodySize);
		    memcpy((char *)functionPara, paramBuffer, PARAMNUMBER*sizeof(activeFunc));
		    /*
		    printf("the param size is %d\n", PARAMNUMBER*sizeof(activeFunc));
		    printf("single param size is %d\n", sizeof(activeFunc));
		    printf("size of int %d, sizeof long %d, size of float %d\n", sizeof(int), sizeof(unsigned long), sizeof(float));
		    for(int i=0; i< 8; i++)
		    {
			printf("the function parameter %d\n", i);
			printf("functionPara numActiveFuncs: %lu\n", functionPara[i].funcNo);
			for(int j=0; j<8; j++)
			{
			    printf("functionPara coordiate: %f*%f*%f\n", functionPara[i].coordinate[j].x, 
				functionPara[i].coordinate[j].y, functionPara[i].coordinate[j].z);
			}
		    }
		    */

		    pthread_mutex_lock(&mutex);
		    paramCounter=1;
		    /*
		    if(paramCounter==3)
			paramCounter = 1;
			*/
		    pthread_mutex_unlock(&mutex);
		    printf("paramcounter is %u\n", paramCounter );
		    paraPtr = (unsigned long)paramBuffer;
		    /*
		    if(paramCounter==2)
			paraPtr = (unsigned long)paramBuffer;
		    else
			paraPtr += PARAMNUMBER*sizeof(activeFunc);
			*/
		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    status |= (1<<3);
		    lastCmd &= ~(1<<1);
		    break;
		}
		headPtr = tailPtr;
		break;
	    case (1<<4):
		if(tailPtr = (char *)memmem(headPtr, n, "<\\DATA", 6))
		{
		    bodySize = tailPtr-bodyPtr;
		    pthread_mutex_lock(&mutex);
		    imageSourceReady = true;
		    memcpy((unsigned char *)bufferPtr, (unsigned char *)bodyPtr, bodySize);
		    pthread_mutex_unlock(&mutex);
		    bufferPtr = (unsigned long)imageBufferSource;
		    printf("<\\DATA tail found \n");	
		    status &= ~((1<<0)|(1<<2)|(1<<4));
		    status |= (1<<5);
		    lastCmd &= ~(1<<2);
		    break;
		}
		headPtr = tailPtr;
		break;
	    case (1<<1):
	    case (1<<3):
	    case (1<<5):
		printf("looking for a head \n");
		if(tailPtr = (char *)memmem(headPtr, n, "<COMD" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("head found %s\n", tailPtr);
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    status |= (1<<0);
		    lastCmd |= (1<<0);
		    break;
		}else if(tailPtr = (char *)memmem(headPtr, n, "<PARA" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("head found %s\n", tailPtr);
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    status |= (1<<2);
		    lastCmd |= (1<<1);
		    break;
		}else if(tailPtr = (char *)memmem(headPtr,n, "<DATA" , 5)) 
		{
		    bodyPtr = tailPtr + 5;
		    printf("<DATA head found \n");
		    status &= ~((1<<1)|(1<<3)|(1<<5));
		    status |= (1<<4);
		    lastCmd |= (1<<2);
		    break;
		}
		headPtr = tailPtr;
		break;
	    default:
		break;
	
	}
	if(status & ((1<<0)|(1<<2)|(1<<4))) //found head
	{
	    headPtr = tailPtr + 4;	
	}
	if(status & ((1<<1)|(1<<3)|(1<<5))) //found tail
	{
	    headPtr = tailPtr + 5;	
	}
	n = buffer - (unsigned long)headPtr + buffersize;
    }//while(status)

    switch (status)
    {
	case 0:
	    switch(cmd)
	    {
		case (1<<0):
		    //do something about command;
		    break;
		case (1<<1):
		    bodySize = buffer - (unsigned long)bodyPtr + buffersize;
		    memcpy((char *)paraPtr, bodyPtr, bodySize); 
		    paraPtr += bodySize;
		    break;
		case (1<<2):
		    bodySize = buffer - (unsigned long)bodyPtr + buffersize;
		    pthread_mutex_lock(&mutex);
		    imageSourceReady = false;
		    memcpy((unsigned char *)bufferPtr, (unsigned char *)bodyPtr, bodySize);
		    pthread_mutex_unlock(&mutex);
		    bufferPtr += bodySize;
		    break;
	    }
	    break;
	case (1<<0): 
	    //do something about command    
	    break; 
	case (1<<2):
	    printf("only got the param head\n");
	    bodySize = buffer - (unsigned long)bodyPtr + buffersize;
	    memcpy((char *)paraPtr, bodyPtr, bodySize); 
	    paraPtr += bodySize;
	    break;
	case (1<<4):
	    printf("only got the data head\n");
	    bodySize = buffer - (unsigned long)bodyPtr + buffersize;
	    pthread_mutex_lock(&mutex);
	    imageSourceReady = false;
	    memcpy((unsigned char *)bufferPtr, (unsigned char *)bodyPtr, bodySize);
	    pthread_mutex_unlock(&mutex);
	    bufferPtr += bodySize;
	    break;
	default:
	    break;
    }
    return lastCmd;
}
