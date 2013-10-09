#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "typedef.h"

unsigned char* applytransformold(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	char convexitycheck = 0;
	if(nyT5<(-nyT4*nxT5/nxT1+nyT4)) {convexitycheck = 1;};
	if(nyT5<(nyT2*(nxT5-nxT1)/(1.0-nxT1))) {convexitycheck = 2;};
	if(nyT5>((nyT2-1)*(nxT5-1)/(1-nxT3)+nyT2)) {convexitycheck = 3;};
	if(nyT5>((1.0-nyT4)*nxT5/nxT3+nyT4)) {convexitycheck = 4;};

if (convexitycheck==1)
{
	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				if (Zx2<=nxT1+Zy2*t1x||Zy2<=nyT4+Zx2*t1y) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
					code[k]=0;
				} else
				if (Zx2>nxT1+Zy2*t2x&&Zy2<=nyT5+(Zx2-nxT5)*t2y)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
					code[k]=1;
				} else
				if (Zx2>=nxT5+(Zy2-nyT5)*t3x&&Zy2>nyT5+(Zx2-nxT5)*t3y)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
					code[k]=2;
				} else
				if (Zx2<nxT5+(Zy2-nyT5)*t4x&&Zy2>nyT4+Zx2*t4y)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
					code[k]=3;
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0) 
				{
					Zx2=0;
				} else
				if (Zx2>1) 
				{
					Zx2=1;
				};
				if (Zy2<0) 
				{
					Zy2=0;
				} else
				if (Zy2>1) 
				{
					Zy2=1;
				};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
};
if (convexitycheck==2)
{
	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				if (Zx2<=nxT1+Zy2*t1x&&Zy2<=nyT4+Zx2*t1y) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
					code[k]=0;
				} else
				if (Zx2>nxT1+Zy2*t2x||Zy2<=nyT5+(Zx2-nxT5)*t2y)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
					code[k]=1;
				} else
				if (Zx2>=nxT5+(Zy2-nyT5)*t3x&&Zy2>nyT5+(Zx2-nxT5)*t3y)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
					code[k]=2;
				} else
				if (Zx2<nxT5+(Zy2-nyT5)*t4x&&Zy2>nyT4+Zx2*t4y)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
					code[k]=3;
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0) 
				{
					Zx2=0;
				} else
				if (Zx2>1) 
				{
					Zx2=1;
				};
				if (Zy2<0) 
				{
					Zy2=0;
				} else
				if (Zy2>1) 
				{
					Zy2=1;
				};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
};
if (convexitycheck==3)
{
	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				if (Zx2<=nxT1+Zy2*t1x&&Zy2<=nyT4+Zx2*t1y) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
					code[k]=0;
				} else
				if (Zx2>nxT1+Zy2*t2x&&Zy2<=nyT5+(Zx2-nxT5)*t2y)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
					code[k]=1;
				} else
				if (Zx2>=nxT5+(Zy2-nyT5)*t3x||Zy2>nyT5+(Zx2-nxT5)*t3y)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
					code[k]=2;
				} else
				if (Zx2<nxT5+(Zy2-nyT5)*t4x&&Zy2>nyT4+Zx2*t4y)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
					code[k]=3;
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0) 
				{
					Zx2=0;
				} else
				if (Zx2>1) 
				{
					Zx2=1;
				};
				if (Zy2<0) 
				{
					Zy2=0;
				} else
				if (Zy2>1) 
				{
					Zy2=1;
				};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
};
if (convexitycheck==4)
{
	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				if (Zx2<=nxT1+Zy2*t1x&&Zy2<=nyT4+Zx2*t1y) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
					code[k]=0;
				} else
				if (Zx2>nxT1+Zy2*t2x&&Zy2<=nyT5+(Zx2-nxT5)*t2y)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
					code[k]=1;
				} else
				if (Zx2>=nxT5+(Zy2-nyT5)*t3x&&Zy2>nyT5+(Zx2-nxT5)*t3y)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
					code[k]=2;
				} else
				if (Zx2<nxT5+(Zy2-nyT5)*t4x||Zy2>nyT4+Zx2*t4y)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
					code[k]=3;
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0) 
				{
					Zx2=0;
				} else
				if (Zx2>1) 
				{
					Zx2=1;
				};
				if (Zy2<0) 
				{
					Zy2=0;
				} else
				if (Zy2>1) 
				{
					Zy2=1;
				};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
};
if (convexitycheck==0)
{
	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				if (Zx2<=nxT1+Zy2*t1x&&Zy2<=nyT4+Zx2*t1y) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
					code[k]=0;
				} else
				if (Zx2>nxT1+Zy2*t2x&&Zy2<=nyT5+(Zx2-nxT5)*t2y)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
					code[k]=1;
				} else
				if (Zx2>=nxT5+(Zy2-nyT5)*t3x&&Zy2>nyT5+(Zx2-nxT5)*t3y)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
					code[k]=2;
				} else
				if (Zx2<nxT5+(Zy2-nyT5)*t4x&&Zy2>nyT4+Zx2*t4y)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
					code[k]=3;
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0) 
				{
					Zx2=0;
				} else
				if (Zx2>1) 
				{
					Zx2=1;
				};
				if (Zy2<0) 
				{
					Zy2=0;
				} else
				if (Zy2>1) 
				{
					Zy2=1;
				};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
};

	delete(code);

	return ImageT;
};





//this is simpler than above and may even run slightly quicker
unsigned char* applytransform(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;
	for(i=0; i<6; i++)
	    printf("arglhs is %f\n", argslhs[i]);
	for(i=0; i<6; i++)
	    printf("argrhs is %f\n", argsrhs[i]);

	printf("f1_x4 is %f\n", f1_x4);
	printf("f2_x4 is %f\n", f2_x4);
	printf("f3_x6 is %f\n", f1_x4);
	printf("f4_x4 is %f\n", f1_x4);

	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here, the first bit may be a quicker version, may be a problem with it though
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				/* //this would be a more thorough check of all of the regions one at a time.
				if (Zy2>=Zx2*tt1&&Zy2<=nyT4+Zx2*t1y) {code[k]=0;}; 
				if (Zy2<Zx2*tt1&&Zx2<=nxT1+Zy2*t1x) {code[k]=0;};
				if (Zy2>=(1.0-Zx2)*tt2&&Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;};
				if (Zy2<(1.0-Zx2)*tt2&&Zx2>nxT1+Zy2*t2x) {code[k]=1;};
				if (Zy2<1.0-(1.0-Zx2)*tt3&&Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;};
				if (Zy2>=1.0-(1.0-Zx2)*tt3&&Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;};
				if (Zy2<1.0-Zx2*tt4&&Zy2>nyT4+Zx2*t4y) {code[k]=3;};
				if (Zy2>=1.0-Zx2*tt4&&Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;};
				*/
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0.0) {Zx2=0.0;} else if (Zx2>1.0) {Zx2=1.0;};
				if (Zy2<0.0) {Zy2=0.0;} else if (Zy2>1.0) {Zy2=1.0;};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1.0-Zx1*(1.0-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1.0-Zx1*(1.0-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1.0-Zy1*(1.0-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1.0-Zy1*(1.0-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) round((xres-1)*Zx1);
			iZy1=(int) round((yres-1)*(1.0-Zy1));
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};

	delete(code);

	return ImageT;
};






unsigned char* applytransformHR(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres,int hxres, int hyres, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;


	for   (i=0;i<hyres;i++)
	{	
		for	(j=0;j<hxres;j++)
		{
			iZ=3*(i*hxres+j);			
			Zx2 = (double) j/(hxres-1);
			Zy2 = (double) 1.0-1.0*i/(hyres-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here, the first bit may be a quicker version, may be a problem with it though
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};

	delete(code);

	return ImageT;
};







unsigned char* applytransformZ(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength, double blX, double wX, double blY, double hY)
{
	//codelength = 2*codelength;
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);
			Zx2 = (double) blX+wX*j/(resolution-1);
			Zy2 = (double) 1.0-blY-hY*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here, the first bit may be a quicker version, may be a problem with it though
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here				
				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (xres-1)*Zx1+0.5;
			iZy1=(int) (yres-1)*(1.0-Zy1)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
	
	delete(code);

	return ImageT;
};






unsigned char* applytransformD(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength, double dblX, double dwX, double dblY, double dhY)
{
	//codelength = 2*codelength;
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) 1.0*j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here, the first bit may be a quicker version, may be a problem with it though
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1 = (int) (xres-1)*(dwX*Zx1+dblX)+0.5;
			iZy1 = (int) (yres-1)*(dhY*(1.0-Zy1)+dblY)+0.5;
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
	
	delete(code);

	return ImageT;
};






unsigned char* applytransform1(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	
	//note the following is not needed with double buffering, it has been deleted from the other 3 real time transforms
	//unsigned char* ImageT2 = new unsigned char[3*resolution*resolution];

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	printf("enter applytransform1\n");
	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=0;i<resolution;i+=2)
	{	
		for	(j=0;j<resolution;j+=2)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) 1.0*j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here			
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if(isnan(Zx2))
				    Zx2 = 0.0;
				if(isnan(Zy2))
				    Zy2 = 0.0;

				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) round((xres-1)*Zx1);
			iZy1=(int) round((yres-1)*(1.0-Zy1));
			iZ1=3*(iZy1*xres+iZx1);
			//note the following is not needed with double buffering, it has been deleted from the other 3 real time transforms
			//ImageT2[iZ]=ImageD[iZ1];
			//ImageT2[1+iZ]=ImageD[1+iZ1];
			//ImageT2[2+iZ]=ImageD[2+iZ1];
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};

	//note the following is not needed with double buffering, it has been deleted from the other 3 real time transforms
	//for (i=0;i<resolution;i+=2)
	//{
	//	for (j=0;j<resolution;j+=2)
	//	{
	//		k = 3*(j*resolution+i);
	//		ImageT[k] = ImageT2[k];
	//		ImageT[k+1] = ImageT2[k+1];
	//		ImageT[k+2] = ImageT2[k+2];
	//	};
	//};
	//delete(ImageT2);
	
	delete(code);

	return ImageT;
};






unsigned char* applytransform2(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	printf("enter applytransform2\n");
	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=1;i<resolution;i+=2)
	{	
		for	(j=0;j<resolution;j+=2)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) 1.0*j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here			
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if(isnan(Zx2))
				    Zx2 = 0.0;
				if(isnan(Zy2))
				    Zy2 = 0.0;

				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) round((xres-1)*Zx1);
			iZy1=(int) round((yres-1)*(1.0-Zy1));
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
	
	delete(code);

	return ImageT;
};






unsigned char* applytransform3(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char code[codelength];

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	printf("enter applytransform3\n");
	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	Zx1=Zy1=Zx2=Zy2=Zxt1=Zxt2=Zyt1=Zyt2=t=tt=0.0;
	iZ=iZ1=iZx1=iZy1=0;

	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=0;i<resolution;i+=2)
	{	
		for	(j=1;j<resolution;j+=2)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) 1.0*j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here			
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if(isnan(Zx2))
				    Zx2 = 0.0;
				if(isnan(Zy2))
				    Zy2 = 0.0;

				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) round((xres-1)*Zx1);
			iZy1=(int) round((yres-1)*(1.0-Zy1));
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};
	
	printf("finish computation in transform3\n");
	return ImageT;
};






unsigned char* applytransform4(unsigned char* ImageD, unsigned char* ImageT, int xres, int yres, int resolution, double* argslhs, double* argsrhs, int codelength)
{
	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char code[codelength];

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node
	Zx1=Zy1=Zx2=Zy2=Zxt1=Zxt2=Zyt1=Zyt2=t=tt=0.0;
	iZ=iZ1=iZx1=iZy1=0;

	printf("enter applytransform4\n");

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;

	for   (i=1;i<resolution;i+=2)
	{	
		for	(j=1;j<resolution;j+=2)
		{
			iZ=3*(i*resolution+j);			
			Zx2 = (double) 1.0*j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here			
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if(isnan(Zx2))
				    Zx2 = 0.0;
				if(isnan(Zy2))
				    Zy2 = 0.0;
				if (Zx2<0.0) {Zx2=0.0;} else {if (Zx2>1.0) {Zx2=1.0;};};
				if (Zy2<0.0) {Zy2=0.0;} else {if (Zy2>1.0) {Zy2=1.0;};};
			};

			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1-Zx1*(1-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1-Zy1*(1-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1-Zy1*(1-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int)round((xres-1)*Zx1);
			iZy1=(int)round((yres-1)*(1.0-Zy1));
			iZ1=3*(iZy1*xres+iZx1);
			ImageT[iZ]=ImageD[iZ1];
			ImageT[1+iZ]=ImageD[1+iZ1];
			ImageT[2+iZ]=ImageD[2+iZ1];
		
		//we continue the two for loops until the are done
		};
	};

	printf("finish computation in transform4\n");
	return ImageT;
};











unsigned int* filtermaker(unsigned int* FilterData, int resolution, double* argslhs, double* argsrhs, int codelength){

	int i,j,k,kk;
	double Zx1,Zy1,Zx2,Zy2,Zxt1,Zxt2,Zyt1,Zyt2,t,tt;
	int iZ,iZ1,iZx1,iZy1;
	unsigned char* code = new unsigned char[codelength];	

	double nxT1 = argsrhs[0]; //The node on the bottom edge (the line y=0)
	double nyT2 = argsrhs[1]; //The node on the right edge (the line x=1)
	double nxT3 = argsrhs[2]; //The node on the top edge (the line y=1)
	double nyT4 = argsrhs[3]; //The node on the left edge (the line x=0)
	double nxT5 = argsrhs[4]; //The x coordinate for the centre node 
	double nyT5 = argsrhs[5]; //The y coordinate for the centre node

	//	The following prevents errors in calculating inverse bilinears. (if any of the values in the "if" statements below are equal then you can get 0 denominators which results in infinity errors)
	//	An alternative would be redefine the inverses for various cases but this is a much cheaper method and the result of the small change is unnoticable in the final output
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT3==nxT5) {nxT5=nxT5-0.00000001;};
	if (nxT1==nxT5) {nxT5=nxT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT4==nyT5) {nyT5=nyT5-0.00000001;};
	if (nyT2==nyT5) {nyT5=nyT5-0.00000001;};

	//The following are constants that are used for calculating which inverse bilinear to calculate and then for applying the appropriate inverse bilinears
	double t1x = (nxT5-nxT1)/nyT5;
	double t1y = (nyT5-nyT4)/nxT5;
	double t2x = (nxT5-nxT1)/nyT5;
	double t2y = (nyT2-nyT5)/(1-nxT5);
	double t3x = (nxT3-nxT5)/(1-nyT5);
	double t3y = (nyT2-nyT5)/(1-nxT5);
	double t4x = (nxT3-nxT5)/(1-nyT5);
	double t4y = (nyT5-nyT4)/nxT5;
	double tt1 = nyT5/nxT5;
	double tt2 = nyT5/(1-nxT5);
	double tt3 = (1-nyT5)/(1-nxT5);
	double tt4 = (1-nyT5)/nxT5;
	double f1_x1 = nxT1* nyT4;
	double f1_x2 = nyT4 - nyT5;
	double f1_x3 = nxT5 - nxT1;
	double f1_x4 = (double) 4* nxT1* (nxT5 - nxT1)* nyT4;
	double f1_x5 = (double) 1/(2* nxT1* (nyT4 - nyT5));
	double f1_y1 = (double) 1/(2* (nxT5 - nxT1)* nyT4);
	double f2_x1 = nyT5 - nyT2;
	double f2_x2 = -nyT5 + nxT1 *nyT2;
	double f2_x3 = nxT1 - nxT5;
	double f2_x4 = (double) 4* (1 - nxT1)* nyT2* (nyT5 - nyT2);
	double f2_x5 = nyT5 + nyT2* (-2 + nxT1);
	double f2_x6 = (double) 1/(2* (nxT1 - nxT5)* nyT2);
	double f2_y1 = (double) 1/(2* (1 - nxT1)* (nyT5 - nyT2));
	double f3_x1 = (double) 1/(2* (1 - nxT3)* (nyT2 - nyT5));
	double f3_x2 = -1 + nxT5 - nyT5 - nyT2* (-2 + nxT3);
	double f3_x3 = (nyT5 - nyT2);
	double f3_x5 = (nxT3 - nxT5);
	double f3_x6 = (double) 4* (1 - nxT3)* (nxT5 - nxT3)* (1 - nyT2);
	double f3_x7 = 1 + nxT5 - nyT5 + nxT3* (-2 + nyT2);
	double f3_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT2));
	double f3_y2 = 1 - 2* nxT3 + nxT5 + nxT3* nyT2 - nyT5;
	double f4_x1 = nxT3* nyT4 - nxT5;
	double f4_x2 = nyT4 - nyT5;
	double f4_x3 = nxT5 - nxT3;
	double f4_x4 = (double) 4* nxT3* (nxT3 - nxT5)* (1 - nyT4);
	double f4_x5 = nxT5 + nxT3* (-2 + nyT4);
	double f4_x6 = (double) 1/(2* nxT3* (nyT4 - nyT5));
	double f4_y1 = (double) 1/(2* (nxT5 - nxT3)* (1 - nyT4));
	double f4_y2 = -2* nxT3 + nxT5 + nxT3* nyT4;


	for   (i=0;i<resolution;i++)
	{	
		for	(j=0;j<resolution;j++)
		{
			iZ=i*resolution+j;			
			Zx2 = (double) j/(resolution-1);
			Zy2 = (double) 1.0-1.0*i/(resolution-1);
			// in this loop we find the code of the given point from the target IFS, remember j is x 
			//coordinate and i is y coordinate
			for	(k=0;k<codelength;k++)
			{
				//check the region here, the first bit may be a quicker version, may be a problem with it though
				for (kk=0;kk<1;kk++) //this loop looks silly and unessesary but it allows us to 'break' from it when we have found the right code, this is particularly helpful because it saves doing all of the checks if the code is found first off.
				{
					if (Zy2>=Zx2*tt1)
					{
						if (Zy2<=nyT4+Zx2*t1y) {code[k]=0;break;};
					} else
					{
						if (Zx2<=nxT1+Zy2*t1x) {code[k]=0;break;};
					};
					if (Zy2<1.0-(1.0-Zx2)*tt3)
					{
						if (Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;break;};
					} else
					{
						if (Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;break;};
					};
					if (Zy2>=(1.0-Zx2)*tt2)
					{
						if (Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;break;};
					} else
					{
						if (Zx2>nxT1+Zy2*t2x) {code[k]=1;break;};
					};
					if (Zy2>=1.0-Zx2*tt4)
					{
						if (Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;break;};
					} else
					{
						if (Zy2>nyT4+Zx2*t4y) {code[k]=3;break;};
					};
				};
				/* //this would be a more thorough check of all of the regions one at a time.
				if (Zy2>=Zx2*tt1&&Zy2<=nyT4+Zx2*t1y) {code[k]=0;}; 
				if (Zy2<Zx2*tt1&&Zx2<=nxT1+Zy2*t1x) {code[k]=0;};
				if (Zy2>=(1.0-Zx2)*tt2&&Zy2<=nyT5+(Zx2-nxT5)*t2y) {code[k]=1;};
				if (Zy2<(1.0-Zx2)*tt2&&Zx2>nxT1+Zy2*t2x) {code[k]=1;};
				if (Zy2<1.0-(1.0-Zx2)*tt3&&Zy2>nyT5+(Zx2-nxT5)*t3y) {code[k]=2;};
				if (Zy2>=1.0-(1.0-Zx2)*tt3&&Zx2>=nxT5+(Zy2-nyT5)*t3x) {code[k]=2;};
				if (Zy2<1.0-Zx2*tt4&&Zy2>nyT4+Zx2*t4y) {code[k]=3;};
				if (Zy2>=1.0-Zx2*tt4&&Zx2<nxT5+(Zy2-nyT5)*t4x) {code[k]=3;};
				*/
				//do inverse function
				if (code[k]==0) //in each if loop we see if the point is in the range of one of the bilinear functions and if it is we apply the corresponding iverse and record the number of the function into the code
				{	
					t = sqrt( f1_x4* Zy2 + pow(f1_x2* Zx2 + f1_x3* Zy2 - f1_x1,2));
					tt = f1_x2* Zx2 + f1_x3* Zy2;
					Zxt2 = (f1_x1 + tt - t)* f1_x5;
					Zyt2 = (tt - f1_x1 + t)* f1_y1;
				} else
				if (code[k]==1)
				{	
					t = sqrt( f2_x4* (1 - Zx2) + pow(-f2_x1* Zx2 + f2_x5 - f2_x3* Zy2,2));
					tt = f2_x1* Zx2 + f2_x3* Zy2;
					Zxt2 = f2_y1* (f2_x5 - tt + t);
					Zyt2 = (tt + f2_x2 + t)* f2_x6;
				} else
				if (code[k]==2)
				{	
					t = sqrt(f3_x6* (-1 + Zy2) + pow(f3_x7 + f3_x3* Zx2 + f3_x5* Zy2,2));
					tt = f3_x3* Zx2 + f3_x5* Zy2;
					Zxt2 = f3_x1* (f3_x2 + tt + t);
					Zyt2 = f3_y1* (f3_y2 + tt - t);
				} else
				if (code[k]==3)
				{	
					t = sqrt(f4_x4* (-1 + Zy2) + pow(f4_x5 - f4_x2* Zx2 - f4_x3* Zy2,2));
					tt = f4_x2* Zx2 + f4_x3* Zy2;
					Zxt2 = (f4_x1 + tt + t)* f4_x6;
					Zyt2 = f4_y1* (f4_y2 - tt + t);
				};
				// again we use temporary variables which we now reassign to the actual variables.
				Zx2 = Zxt2;
				Zy2 = Zyt2;

				// sometimes small errors in calculating inverse bilinears put us outside (only by very small amounts) the range so we prevent that here
				if (Zx2<0.0) {Zx2=0.0;} else if (Zx2>1.0) {Zx2=1.0;};
				if (Zy2<0.0) {Zy2=0.0;} else if (Zy2>1.0) {Zy2=1.0;};
			};
			
			//Here we just initialise the values for applying the code to the colourstealing IFS. We could just choose (0,0) but I find it nicer to choose the last value obtained when finding the code
			Zx1 = Zx2;
			Zy1 = Zy2;
			//we apply the code to the colour stealing IFS
			for	(k=codelength-1;k>=0;k--)
			{	
				if (code[k]==0)
				{	
					Zxt1 = Zx1*(argslhs[0]+Zy1*(argslhs[4]-argslhs[0]));
					Zyt1 = Zy1*(argslhs[3]+Zx1*(argslhs[5]-argslhs[3]));
				} else
				if (code[k]==1)
				{	
					Zxt1 = 1.0-Zx1*(1.0-argslhs[0]+Zy1*(argslhs[0]-argslhs[4]));
					Zyt1 = Zy1*(argslhs[1]+Zx1*(argslhs[5]-argslhs[1]));
				} else
				if (code[k]==2)
				{	
					Zxt1 = 1.0-Zx1*(1.0-argslhs[2]+Zy1*(argslhs[2]-argslhs[4]));
					Zyt1 = 1.0-Zy1*(1.0-argslhs[1]+Zx1*(argslhs[1]-argslhs[5]));
				} else
				if (code[k]==3)
				{	
					Zxt1 = Zx1*(argslhs[2]+Zy1*(argslhs[4]-argslhs[2]));
					Zyt1 = 1.0-Zy1*(1.0-argslhs[3]+Zx1*(argslhs[3]-argslhs[5]));
				};
				Zx1 = Zxt1;
				Zy1 = Zyt1;
			};
			//We add in this final check just in case anything unexpected may occur
			if (Zx1<0.0) {Zx1=0.0;} else {if (Zx1>1.0) {Zx1=1.0;};};
			if (Zy1<0.0) {Zy1=0.0;} else {if (Zy1>1.0) {Zy1=1.0;};};

			//After applying the code we find the corresponding array coordinates for the picture, we then assign the colour to be the values taken from that array.
			iZx1=(int) (resolution-1)*Zx1+0.5;
			iZy1=(int) (resolution-1)*(1.0-Zy1)+0.5;
			iZ1=iZy1*65536+iZx1;
			FilterData[iZ]=iZ1;
		
		};
	};

	delete(code);


	return FilterData;
};
