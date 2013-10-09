#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "chaosgame.h"
#include "typedef.h"

extern activeFunc functionPara[10];

unsigned long transformImage(unsigned char *imageBuffer, unsigned char* backgroundColor)
{
    frameBuffer frameTarget, frameSource;    
    double xNew, yNew, xOld, yOld, denominator;
    unsigned long iteration = 0;
    unsigned long resolution = 0;
    unsigned long i, j, randomMax, random;
    unsigned long pos, posX, posY;
    unsigned long numFuncs;
    frameTarget.image = imageBuffer;
    frameSource.image = backgroundColor;
    numFuncs = functionPara[0].numActiveFuncs;
    float prob[numFuncs+1];
    resolution =functionPara[0].resolution.xLength*functionPara[0].resolution.yWidth; 
    for(i=0; i<resolution;i++)
    {
	frameTarget.pixel[i].red = frameSource.pixel[i].red;
	frameTarget.pixel[i].green = frameSource.pixel[i].green;
	frameTarget.pixel[i].blue = frameSource.pixel[i].blue;
    }

    if(numFuncs == 0) return 0;

    srand((unsigned)time(NULL));
    randomMax = RAND_MAX;

    iteration = numFuncs*resolution;
    if (numFuncs<4) 
	iteration = 4*resolution;

    xNew = yNew = xOld = yOld = denominator = 0.0;

    computeProb(prob);
    for(i=0; i<100; i++)
    {
	random = rand(); 
	for(j=0; j<numFuncs; j++)
	{
	    if(!(random < round(randomMax*prob[j]))&&(!(random > round(randomMax*prob[j+1]))))
	    {
		denominator = functionPara[j].transPara[8] + functionPara[j].transPara[9] * xOld
				+functionPara[j].transPara[10] * yOld;
		xNew = (functionPara[j].transPara[0]+functionPara[j].transPara[1] * xOld
		    +(functionPara[j].transPara[2]+functionPara[j].transPara[3] * xOld) * yOld)/denominator;
		yNew = (functionPara[j].transPara[4]+functionPara[j].transPara[5]*xOld
		    +(functionPara[j].transPara[6]+functionPara[j].transPara[7]*xOld)*yOld)/denominator;
		break;
	    }
	}

	xOld = xNew;
	yOld = yNew;
    }

    for(i=100; i<iteration; i++)
    {
	random = rand(); 
	for(j=0; j<numFuncs; j++)
	{
	    if(!(random < round(randomMax*prob[j]))&&(!(random > round(randomMax*prob[j+1]))))
	    {
		denominator = functionPara[j].transPara[8] + functionPara[j].transPara[9] * xOld
				+functionPara[j].transPara[10] * yOld;
		xNew = (functionPara[j].transPara[0]+functionPara[j].transPara[1] * xOld
		    +(functionPara[j].transPara[2]+functionPara[j].transPara[3] * xOld) * yOld)/denominator;
		yNew = (functionPara[j].transPara[4]+functionPara[j].transPara[5]*xOld
		    +(functionPara[j].transPara[6]+functionPara[j].transPara[7]*xOld)*yOld)/denominator;
		break;
	    }
	}

	if((!(xNew<0.0))&&(!(xNew>1.0))&&(!(yNew<0.0))&&(!(yNew>1.0)))
	{
	    posX = round((functionPara[0].resolution.xLength-1)*xNew);	    	
	    posY = round((functionPara[0].resolution.yWidth-1)*(1.0 - yNew));
	    pos = (functionPara[0].resolution.xLength*posY + posX);
	    frameTarget.pixel[pos].red = functionPara[j].colorMap.red;
	    frameTarget.pixel[pos].green = functionPara[j].colorMap.green;
	    frameTarget.pixel[pos].blue = functionPara[j].colorMap.blue;
	}
	if(abs(xNew )>1000) xNew /= 10.0;
	if(abs(yNew)>1000) yNew /= 10.0;

	xOld = xNew;
	yOld = yNew;
    
    }
    return resolution*3;
}

void computePara()
{
    int i=0, j=0;
    unsigned long numFuncs = functionPara[0].numActiveFuncs;
    /*this for loop can be parallelized*/
    for(i=0; i<numFuncs; i++)
    {
	switch(functionPara[i].transType)
	{
	    case 1://affine transformation
	    case 2:
		functionPara[i].transPara[3]=0.0;
		functionPara[i].transPara[7]=0.0;
		functionPara[i].transPara[8]=1.0;
		functionPara[i].transPara[9]=0.0;
		functionPara[i].transPara[10]=0.0;
		functionPara[i].transPara[0]=functionPara[i].coordinate[0].x;
		functionPara[i].transPara[1]=functionPara[i].coordinate[1].x-functionPara[i].coordinate[0].x;
		functionPara[i].transPara[2]=functionPara[i].coordinate[3].x-functionPara[i].coordinate[0].x;
		functionPara[i].transPara[4]=functionPara[i].coordinate[0].y;
		functionPara[i].transPara[5]=functionPara[i].coordinate[1].y - functionPara[i].coordinate[0].y;
		functionPara[i].transPara[6]=functionPara[i].coordinate[3].y - functionPara[i].coordinate[0].y;
		break;
	    case 3://projective
		functionPara[i].transPara[3]=0.0;
		functionPara[i].transPara[7]=0.0;
		functionPara[i].transPara[8]=1.0;
		functionPara[i].transPara[9] =((functionPara[i].coordinate[2].y-functionPara[i].coordinate[3].y)*
		    (functionPara[i].coordinate[1].x-functionPara[i].coordinate[0].x)-
		    (functionPara[i].coordinate[2].x-functionPara[i].coordinate[3].x)*
		    (functionPara[i].coordinate[1].y-functionPara[i].coordinate[0].y))/
		    ((functionPara[i].coordinate[2].y-functionPara[i].coordinate[3].y)*
		    (functionPara[i].coordinate[2].x- functionPara[i].coordinate[1].x)-
		    (functionPara[i].coordinate[2].x-functionPara[i].coordinate[3].x)*
		    (functionPara[i].coordinate[2].y-functionPara[i].coordinate[1].y));
		if((functionPara[i].coordinate[2].x-functionPara[i].coordinate[3].x))
		{
		    functionPara[i].transPara[10] = ((functionPara[i].coordinate[1].x-functionPara[i].coordinate[0].x+
			functionPara[i].coordinate[3].x-functionPara[i].coordinate[2].x)-
			(functionPara[i].coordinate[2].x- functionPara[i].coordinate[1].x)*
			functionPara[i].transPara[9])/(functionPara[i].coordinate[2].x-functionPara[i].coordinate[3].x);
		} else
		{
		    functionPara[i].transPara[10] = ((functionPara[i].coordinate[1].y-functionPara[i].coordinate[0].y+
		    functionPara[i].coordinate[3].y-functionPara[i].coordinate[2].y)-
		    (functionPara[i].coordinate[2].y-functionPara[i].coordinate[1].y)*
		    functionPara[i].transPara[9])/(functionPara[i].coordinate[2].y-functionPara[i].coordinate[3].y);
		}
		functionPara[i].transPara[0]=functionPara[i].coordinate[0].x;
		functionPara[i].transPara[1]=functionPara[i].coordinate[1].x*(1.0+functionPara[i].transPara[9])-
		    functionPara[i].coordinate[0].x;
		functionPara[i].transPara[2]=functionPara[i].coordinate[3].x*(1.0+functionPara[i].transPara[10])-
		    functionPara[i].coordinate[0].x;
		functionPara[i].transPara[4]=functionPara[i].coordinate[0].y;
		functionPara[i].transPara[5]=functionPara[i].coordinate[1].y*(1.0+functionPara[i].transPara[9])-
		    functionPara[i].coordinate[0].y;
		functionPara[i].transPara[6]=functionPara[i].coordinate[3].y*(1.0+functionPara[i].transPara[10])-
		    functionPara[i].coordinate[0].y;
		break;
	    case 4://bilinear
		functionPara[i].transPara[8]=1.0;
		functionPara[i].transPara[9]=0.0;
		functionPara[i].transPara[10]=0.0;
		functionPara[i].transPara[0]=functionPara[i].coordinate[0].x;
		functionPara[i].transPara[1]=functionPara[i].coordinate[1].x-functionPara[i].coordinate[0].x;
		functionPara[i].transPara[2]=functionPara[i].coordinate[3].x-functionPara[i].coordinate[0].x;
		functionPara[i].transPara[3]=functionPara[i].coordinate[2].x-functionPara[i].coordinate[3].x-
		    functionPara[i].coordinate[1].x+functionPara[i].coordinate[0].x;
		functionPara[i].transPara[4]=functionPara[i].coordinate[0].y;
		functionPara[i].transPara[5]=functionPara[i].coordinate[1].y-functionPara[i].coordinate[0].y;
		functionPara[i].transPara[6]=functionPara[i].coordinate[3].y-functionPara[i].coordinate[0].y;
		functionPara[i].transPara[7]=functionPara[i].coordinate[2].y-functionPara[i].coordinate[3].y-
		    functionPara[i].coordinate[1].y+functionPara[i].coordinate[0].y;
		break;
	    default:
		break;
	
	}
	/*
	for(int j=0; j<11; j++)
	    printf("compute para %d is %f\n", i, functionPara[i].transPara[j]);
	printf("compute prara prob is %f\n", functionPara[i].prob);
	*/
    }//end for
}

void computeProb(float *prob)
{
    int i=0;
    unsigned long numFuncs = functionPara[0].numActiveFuncs;
    float temp = 0.0;
    if(functionPara[0].prob == -1.0)
    {
	for(i=0;i<numFuncs;i++)
	{
	    functionPara[i].prob =abs(((functionPara[i].transPara[0]+functionPara[i].transPara[1])/
		(functionPara[i].transPara[8]+ functionPara[i].transPara[9])- functionPara[i].transPara[0])*
		((functionPara[i].transPara[6]+functionPara[i].transPara[4])/
		(functionPara[i].transPara[8]+functionPara[i].transPara[10])-functionPara[i].transPara[4])-
		((functionPara[i].transPara[2]+functionPara[i].transPara[0])/
		(functionPara[i].transPara[8]+functionPara[i].transPara[9])-functionPara[i].transPara[0])*
		((functionPara[i].transPara[5]+functionPara[i].transPara[4])/
		(functionPara[i].transPara[8]+functionPara[i].transPara[10])-functionPara[i].transPara[4]));  
	    temp+=functionPara[i].prob;
	}
    }
    else for(i=0;i<numFuncs; i++)
    {
	    temp+=functionPara[i].prob;
    }
    if (temp == 0.0) 
	temp = 1.0;
    prob[0] = 0.0;
    for (i=0;i<numFuncs;i++)
	prob[i+1]= functionPara[i].prob/temp;
    for (i=1;i<numFuncs;i++)
    {
	printf("prob is %f\n", prob[i]);
        prob[i+1]+=prob[i];  //note that sendprobs[0]=0.0 so we need not add it.
    };

}
