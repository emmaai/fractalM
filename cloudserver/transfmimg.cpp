#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include "transfmimg.h"
#include "chaosgame.h"
#include "typedef.h"
#include "3dtransform.h"

activeFunc functionPara[PARAMNUMBER];
unsigned char imageBufferSource[3*1024*1024];
unsigned char imageBufferTarget[3*1024*1024];
unsigned long numActiveFuncs = 0;
extern volatile bool imageSourceReady;
extern volatile bool imageTargetReady;
extern volatile bool paraReady;
extern volatile bool sockClose;
extern pthread_mutex_t mutex;
volatile unsigned long imageTargetSize=0;
extern char paramBuffer[1*PARAMNUMBER*sizeof(functionPara)];
extern volatile unsigned long paramCounter;
unsigned long paramConsumePtr=(unsigned long)paramBuffer;
double arglhs[6], argrhs[6];


void *transfmImage(void *threadarg)
{
    int i= 0, j=0, n=0, rc=0;
    int fd;
    pthread_t thread_transform[2];
    printf("into the transform thread\n");
    while(1)
    {
	if(paramCounter) 
	{
	    printf("consume paracounter is %u\n", paramCounter);
	    
	    memcpy((char *)functionPara, (char *)paramConsumePtr, PARAMNUMBER*sizeof(activeFunc));
	    pthread_mutex_lock(&mutex);
	    paramCounter--;
	    pthread_mutex_unlock(&mutex);
	    /*
	    paramConsumePtr += PARAMNUMBER*sizeof(activeFunc);
	    if(paramConsumePtr >= (unsigned long)paramBuffer + 2*PARAMNUMBER*sizeof(activeFunc))
		paramConsumePtr = (unsigned long)paramBuffer;
		*/

	    numActiveFuncs = functionPara[0].numActiveFuncs; 
	    printf("numActiveFuncs is %d\n", numActiveFuncs);
	    for(i=0; i< 8; i++)
	    {
		printf("the function parameter %d\n", i);
		printf("functionPara numActiveFuncs: %lu\n", functionPara[i].funcNo);
		printf("functionPara color map: red 0x%x\n", functionPara[i].colorMap.red);
		printf("functionPara color map: green 0x%x\n", functionPara[i].colorMap.green);
		printf("functionPara color map: blue 0x%x\n", functionPara[i].colorMap.blue);
		printf("functionPara coordiate: %f*%f\n", functionPara[i].coordinate[0].x, functionPara[i].coordinate[0].y);
		printf("functionPara coordiate: %f*%f\n", functionPara[i].coordinate[1].x, functionPara[i].coordinate[1].y);
		printf("functionPara coordiate: %f*%f\n", functionPara[i].coordinate[2].x, functionPara[i].coordinate[2].y);
		printf("functionPara coordiate: %f*%f\n", functionPara[i].coordinate[3].x, functionPara[i].coordinate[3].y);
		printf("functionPara transtype: %u\n", functionPara[i].transType);
		for(j=0; j<11; j++)
		{
		    printf("functionPara transpara: %f\n", functionPara[i].transPara[j]);
		}
		printf("functionPara prob: %f\n", functionPara[i].prob);
	    }
	    //IFGS
	    /*
	    computePara();
	    imageTargetSize = transformImage(imageBufferTarget, imageBufferSource);
	    */

	    //Lena
	    /*
	    arglhs[0] = functionPara[0].coordinate[1].x;
	    arglhs[1] = functionPara[1].coordinate[2].y;
	    arglhs[2] = functionPara[3].coordinate[3].x;
	    arglhs[3] = functionPara[2].coordinate[0].y;
	    arglhs[4] = functionPara[0].coordinate[2].x;
	    arglhs[5] = functionPara[0].coordinate[2].y;

	    argrhs[0] = functionPara[4].coordinate[1].x;
	    argrhs[1] = functionPara[5].coordinate[2].y;
	    argrhs[2] = functionPara[7].coordinate[3].x;
	    argrhs[3] = functionPara[6].coordinate[0].y;
	    argrhs[4] = functionPara[4].coordinate[2].x;
	    argrhs[5] = functionPara[4].coordinate[2].y;

	    imageTargetSize = 512*512*3;

	    applytransform(imageBufferSource, imageBufferTarget, 512, 512, 512, arglhs, argrhs, 20);
	    */
	    /*
	    rc = pthread_create(&thread_transform[0], NULL, transformLHS, NULL);
 
	    if (rc)
	    {
		 printf("ERROR; return code from pthread_create() is %d\n", rc);
		 exit(-1);
	    }
	    rc = pthread_create(&thread_transform[1], NULL, transformRHS, NULL);
 
	    if (rc)
	    {
		 printf("ERROR; return code from pthread_create() is %d\n", rc);
		 exit(-1);
	    }
	    for(i=0; i<2; i++)
	    {
		rc = pthread_join(thread_transform[i], NULL);
		if (rc)
		{
		    printf("ERROR; return code from pthread_join() is %d\n", rc);
		    exit(-1);
		}
	    }
	    */
	    //3D sphear
	imageTargetSize = functionPara[0].funcNo;
	deterministicTransform((float*) imageBufferSource, (float*) imageBufferTarget,
	    functionPara[0].funcNo/sizeof(float),functionPara[0].coordinate[0].x,functionPara[0].coordinate[1].x, 
	    functionPara[0].coordinate[2].x, functionPara[0].coordinate[3].x);



	    pthread_mutex_lock(&mutex);
	    imageTargetReady = true;
	    pthread_mutex_unlock(&mutex);
	    /*

	    fd = open("imagefile.png", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
	   if(fd < 0){
		printf("ERROR creating the file\n"); 
		continue;
	   }
	    n = write(fd, imageBufferTarget, imageTargetSize);
	    if (n < 0)
	    {
		printf("write file fail! \n");
		continue;
	    }
	    close(fd);
	    */


	}

/*
	if(imageSourceReady)
	{
	    fd = open("imagefile.png", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
	   if(fd < 0){
		printf("ERROR creating the file\n"); 
		continue;
	   }
	    n = write(fd, imageBufferSource, sizeof(imageBufferSource));
	    if (n < 0)
	    {
		printf("write file fail! \n");
		continue;
	    }
	    close(fd);
	    //imageTargetSize = transformImage(imageBufferTarget, imageBufferSource);
	    pthread_mutex_lock(&mutex);
	    imageSourceReady = false;
	    imageTargetReady = true;
	    pthread_mutex_unlock(&mutex);
	}
	*/

	if(sockClose)
	    break;

    }//while(1)
    printf("exit transform thread\n");
    pthread_exit(NULL);
}

void *transformLHS(void *threadarg)
{
    applytransform3(imageBufferSource, imageBufferTarget, 512, 512, 512, arglhs, argrhs, 12);
    applytransform1(imageBufferSource, imageBufferTarget, 512, 512, 512, arglhs, argrhs, 12);
    pthread_exit(NULL);

}

void *transformRHS(void *threadarg)
{
    applytransform4(imageBufferSource, imageBufferTarget, 512, 512, 512, arglhs, argrhs, 12);
    applytransform2(imageBufferSource, imageBufferTarget, 512, 512, 512, arglhs, argrhs, 12);
    pthread_exit(NULL);
}
