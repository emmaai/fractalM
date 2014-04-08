//
//  homeo_test.cpp
//
//
//  Created by Brendan Harding on 28/08/13.
//
//

#include "homeo_3d.h"
#include "db_chaos_3d_parallel.h"
#include<ctime>
#include"omp.h"
#include<sys/time.h>

int LOGGING=1;


int main(){
	
	if (LOGGING>0) printf("Begin: set up IFS\n");

	trilinear fn;
	trilinearIFS ifs1(8);
	double p1[3],p2[3],p3[3],p4[3],p5[3],p6[3],p7[3],p8[3];
	p1[0]=0.0;	p1[1]=0.0;	p1[2]=0.0; // lll coord
	p2[0]=0.5;	p2[1]=0.0;	p2[2]=0.0; // cll coord
	p3[0]=0.0;	p3[1]=0.5;	p3[2]=0.0; // lcl coord
	p4[0]=0.5;	p4[1]=0.5;	p4[2]=0.0; // ccl coord
	p5[0]=0.0;	p5[1]=0.0;	p5[2]=0.5; // llc coord
	p6[0]=0.5;	p6[1]=0.0;	p6[2]=0.5; // clc coord
	p7[0]=0.0;	p7[1]=0.5;	p7[2]=0.5; // lcc coord
	p8[0]=0.3;	p8[1]=0.3;	p8[2]=0.3; // ccc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(0,fn);
	p1[0]=1.0;	p1[1]=0.0;	p1[2]=0.0; // rll coord
	p3[0]=1.0;	p3[1]=0.5;	p3[2]=0.0; // rcl coord
	p5[0]=1.0;	p5[1]=0.0;	p5[2]=0.5; // rlc coord
	p7[0]=1.0;	p7[1]=0.5;	p7[2]=0.5; // rcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(1,fn);
	p1[0]=0.0;	p1[1]=1.0;	p1[2]=0.0; // lrl coord
	p2[0]=0.5;	p2[1]=1.0;	p2[2]=0.0; // crl coord
	p3[0]=0.0;	p3[1]=0.5;	p3[2]=0.0; // lcl coord
	p5[0]=0.0;	p5[1]=1.0;	p5[2]=0.5; // lrc coord
	p6[0]=0.5;	p6[1]=1.0;	p6[2]=0.5; // crc coord
	p7[0]=0.0;	p7[1]=0.5;	p7[2]=0.5; // lcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(2,fn);
	p1[0]=1.0;	p1[1]=1.0;	p1[2]=0.0; // rrl coord
	p3[0]=1.0;	p3[1]=0.5;	p3[2]=0.0; // rcl coord
	p5[0]=1.0;	p5[1]=1.0;	p5[2]=0.5; // rrc coord
	p7[0]=1.0;	p7[1]=0.5;	p7[2]=0.5; // rcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(3,fn);
	p1[0]=0.0;	p1[1]=0.0;	p1[2]=1.0; // llr coord
	p2[0]=0.5;	p2[1]=0.0;	p2[2]=1.0; // clr coord
	p3[0]=0.0;	p3[1]=0.5;	p3[2]=1.0; // lcr coord
	p4[0]=0.5;	p4[1]=0.5;	p4[2]=1.0; // ccr coord
	p5[0]=0.0;	p5[1]=0.0;	p5[2]=0.5; // llc coord
	p6[0]=0.5;	p6[1]=0.0;	p6[2]=0.5; // clc coord
	p7[0]=0.0;	p7[1]=0.5;	p7[2]=0.5; // lcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(4,fn);
	p1[0]=1.0;	p1[1]=0.0;	p1[2]=1.0; // rlr coord
	p3[0]=1.0;	p3[1]=0.5;	p3[2]=1.0; // rcr coord
	p5[0]=1.0;	p5[1]=0.0;	p5[2]=0.5; // rlc coord
	p7[0]=1.0;	p7[1]=0.5;	p7[2]=0.5; // rcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(5,fn);
	p1[0]=0.0;	p1[1]=1.0;	p1[2]=1.0; // lrr coord
	p2[0]=0.5;	p2[1]=1.0;	p2[2]=1.0; // crr coord
	p3[0]=0.0;	p3[1]=0.5;	p3[2]=1.0; // lcr coord
	p5[0]=0.0;	p5[1]=1.0;	p5[2]=0.5; // lrc coord
	p6[0]=0.5;	p6[1]=1.0;	p6[2]=0.5; // crc coord
	p7[0]=0.0;	p7[1]=0.5;	p7[2]=0.5; // lcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(6,fn);
	p1[0]=1.0;	p1[1]=1.0;	p1[2]=1.0; // rrr coord
	p3[0]=1.0;	p3[1]=0.5;	p3[2]=1.0; // rcr coord
	p5[0]=1.0;	p5[1]=1.0;	p5[2]=0.5; // rrc coord
	p7[0]=1.0;	p7[1]=0.5;	p7[2]=0.5; // rcc coord
	fn.set_from_8pts(p1,p2,p3,p4,p5,p6,p7,p8);
	ifs1.set_fn(7,fn);
	
	if (LOGGING>0) printf("Finished: set up IFS\n");
	
	if (LOGGING>0) printf("Begin: Initialize volumes\n");
	
	unsigned int n=2048;
	
	large_volume vol(n,n,n);
	//volume vol(n,n,n);
	if (LOGGING>0) printf("Initialised volume 1\n");
	vol.fill(0);
	if (LOGGING>0) printf("Filled volume 1\n");
	large_volume vol2(n,n,n);
	//volume vol2(n,n,n);
	if (LOGGING>0) printf("Initialised volume 2\n");
	vol2.fill(1);
	if (LOGGING>0) printf("Filled volume 2\n");
	double cen[3];
	cen[0]=0.5;cen[1]=0.5;cen[2]=0.5;
	vol2.add_sphere(0.3,cen);
	if (LOGGING>0) printf("Added sphere to volume 2\n");
	int sphere_count=vol2.num_more_than(1);
	
	if (LOGGING>0) printf("Finished: Initialize volumes\n");
	
	if (LOGGING>0) printf("Begin: First Transformation\n");
	
	// This should run ~1 billion iterations (if n=512)
	// between 4 and 5 seconds on Raijin with 16 cores
	// ~250M its per second
	int mult=2;
	
	//double omp_wt_t=omp_get_wtime();//t=clock();
	struct timeval tp;
	double sec,usec,start,end;
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	//uint64_t len=db_chaos_parallel(ifs1,&vol2,ifs1,&vol,mult);
	uint64_t len=db_chaos_parallel_large(ifs1,&vol2,ifs1,&vol,mult);
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time for db_chaos_parallel: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) len/(end-start)));
	int sum=vol.num_non_zero();
	printf("%d of expected %d\n",sum,(int) (vol.get_size()));
	sum=vol.num_more_than(1);
	printf("%d of expected ~%d\n",sum,sphere_count);
	
	if (LOGGING>0) printf("Finished: First Transformation\n");

	if (n<=512) {
	
		if (LOGGING>0) printf("Begin: Second Transformation\n");
	
		// A run of ~8 billion it (if n=512)
		// about 31-32 seconds on Raijin with 16 cores
		// ~270M its per second
		mult=16;
		gettimeofday(&tp,NULL);
		sec=static_cast<double>(tp.tv_sec);
		usec=static_cast<double>(tp.tv_usec)/1E6;
		start=sec+usec;
		//len=db_chaos_parallel(ifs1,&vol2,ifs1,&vol,mult);
		len=db_chaos_parallel_large(ifs1,&vol2,ifs1,&vol,mult);
		gettimeofday(&tp,NULL);
		sec=static_cast<double>(tp.tv_sec);
		usec=static_cast<double>(tp.tv_usec)/1E6;
		end=sec+usec;
		printf("Time for db_chaos_parallel: %f\n",end-start);
		printf("\tits per second: ~%d\n",(int) ((float) len/(end-start)));
		sum=vol.num_non_zero();
		printf("%d of expected %d\n",sum,(int) (vol.get_size()));
		sum=vol.num_more_than(1);
		printf("%d of expected ~%d\n",sum,sphere_count);
		
		if (LOGGING>0) printf("Finished: Second Transformation\n");

	};

	if (n<=512) {

		if (LOGGING>0) printf("Begin: Third Transformation\n");

		// A run of ~64 billion it
		// about 4 minutes? on Raijin with 16 cores
		// ~270M its per second
		mult=128;
		gettimeofday(&tp,NULL);
		sec=static_cast<double>(tp.tv_sec);
		usec=static_cast<double>(tp.tv_usec)/1E6;
		start=sec+usec;
		//len=db_chaos_parallel(ifs1,&vol2,ifs1,&vol,mult);
		len=db_chaos_parallel_large(ifs1,&vol2,ifs1,&vol,mult);
		gettimeofday(&tp,NULL);
		sec=static_cast<double>(tp.tv_sec);
		usec=static_cast<double>(tp.tv_usec)/1E6;
		end=sec+usec;
		printf("Time for db_chaos_parallel: %f\n",end-start);
		printf("\tits per second: ~%d\n",(int) ((float) len/(end-start)));
		sum=vol.num_non_zero();
		printf("%d of expected %d\n",sum,(int) (vol.get_size()));
		sum=vol.num_more_than(1);
		printf("%d of expected ~%d\n",sum,sphere_count);

		if (LOGGING>0) printf("Finished: Third Transformation\n");
		
	}

	return 0;

};
