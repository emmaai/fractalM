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
#include "trilinear_class.h"
#include "db_class.h"

activeFunc functionPara[PARAMNUMBER];
unsigned char *imageBufferSource;
extern unsigned char *imageBufferTarget;
unsigned long numActiveFuncs = 0;
extern volatile bool imageSourceReady;
extern volatile bool imageTargetReady;
extern volatile bool paraReady;
extern volatile bool sockClose;
extern pthread_mutex_t mutex;
volatile unsigned long imageTargetSize=0;
extern char paramBuffer[PARAMNUMBER*sizeof(functionPara)];
extern volatile unsigned long paramCounter;
extern volatile bool generateHR;
volatile bool displayHR=false;
unsigned long paramConsumePtr=(unsigned long)paramBuffer;
double arglhs[6], argrhs[6];
extern volume *vol1, *vol2, *vol3, *vol4;


void *transfmImage(void *threadarg)
{
    int i= 0, j=0, n=0, rc=0, iter=0;
    int fd;
    pthread_t thread_transform[2];
    double p[8][3];
    trilinear fn;
    trilinearIFS ifs1(8), ifs2(8);
    bool para1=false, para2=false;
    printf("into the transform thread\n");
    while(1)
    {
	if(paramCounter) 
	{
	    printf("consume paracounter is %u\n", paramCounter);
	    pthread_mutex_lock(&mutex);
	    paramCounter--;
	    pthread_mutex_unlock(&mutex);
	    /*
	    paramConsumePtr += PARAMNUMBER*sizeof(activeFunc);
	    if(paramConsumePtr >= (unsigned long)paramBuffer + 2*PARAMNUMBER*sizeof(activeFunc))
		paramConsumePtr = (unsigned long)paramBuffer;
		*/

	    for(i=0; i< 8; i++)
	    {
		printf("the function parameter %d\n", i);
		printf("functionPara numActiveFuncs: %lu\n", functionPara[i].funcNo);
		for(j=0; j<8; j++)
		{
		    printf("functionPara coordiate: %f*%f*%f\n", functionPara[i].coordinate[j].x, 
			functionPara[i].coordinate[j].y, functionPara[i].coordinate[j].z);
		}
	    }
	    if(functionPara[0].funcNo == 1)
	    {
		for(i=0; i<8; i++) 
		{
		    for(j=0; j<8; j++)	
		    {
			p[j][0] = functionPara[i].coordinate[j].x; 
			p[j][1] = functionPara[i].coordinate[j].y; 
			p[j][2] = functionPara[i].coordinate[j].z; 
		    }
		    fn.set_from_8pts(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		    ifs1.set_fn(i, fn);
		}
		para1 = true;
	    }else if(functionPara[0].funcNo == 2)
	    {
		for(i=0; i<8; i++) 
		{
		    for(j=0; j<8; j++)	
		    {
			p[j][0] = functionPara[i].coordinate[j].x; 
			p[j][1] = functionPara[i].coordinate[j].y; 
			p[j][2] = functionPara[i].coordinate[j].z; 
		    }
		    fn.set_from_8pts(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		    ifs2.set_fn(i, fn);
		}
		para2=true;
	    }

	    if(para1&&para2)
	    {
		printf("vol2 pointer is %ul\n", vol2);
		iter = db_chaos_parallel(ifs1,vol1,ifs2,vol2,4);
		while(imageTargetReady);
		memcpy(imageBufferTarget, vol2->slab, vol2->get_size());

		pthread_mutex_lock(&mutex);
		imageTargetReady = true;
		pthread_mutex_unlock(&mutex);

	    }

	}

	if(generateHR && para1 && para2)
	{
		iter = db_chaos_parallel(ifs1,vol3,ifs2,vol4,4);
		while(imageTargetReady);
		memcpy(imageBufferTarget, vol4->slab, vol4->get_size());

		pthread_mutex_lock(&mutex);
		imageTargetReady = true;
		displayHR = true;
		generateHR = false;
		pthread_mutex_unlock(&mutex);

	}


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
