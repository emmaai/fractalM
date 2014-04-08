//
//  large_volume_test.cpp
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


int main(){
	
	unsigned int n=2048;
	
	//volume vol(n,n,n);
	large_volume vol(n,n,n);
	vol.fill(0);
	//volume vol2(n,n,n);
	large_volume vol2(n,n,n);
	vol2.fill(1);
	double cen[3];
	cen[0]=0.5;cen[1]=0.5;cen[2]=0.5;
	vol2.add_sphere(0.3,cen);
	int sphere_count=vol2.num_more_than(1);

	printf("sphere_count: %u\n",sphere_count);
	

	return 0;
};
