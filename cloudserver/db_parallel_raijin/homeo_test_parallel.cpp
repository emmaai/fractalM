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


int main(){
	
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
	
	double x[3],y[3];
	
	printf("\nSome sanity checks!!!!!\n\n");
	
	volume vol(256,256,256);
	// test ability to perform density plot
	ifs1.density_plot(&vol);
	// check percentage of domain covered
	int sum=vol.num_non_zero();
	printf("%d of %d (%f)\n",sum,(int) vol.get_size(),(float)sum/(vol.get_size()));
	
	// a quick test of ability to find correct inverse
	for (int i=1;i<10;i++) {
		x[2]=0.1*i;
		for (int j=1;i<10;i++) {
			x[1]=0.1*j;
			for (int k=1;i<10;i++) {
				x[0]=0.1*k;
				ifs1.find_domain_and_invert(x,y);
			}
		}
	}
	
	// quick test of volume
	volume vol2(256,256,256);
	vol2.fill(1);
	double cen[3];
	cen[0]=0.5;cen[1]=0.5;cen[2]=0.5;
	vol2.add_sphere(0.3,cen);
	int sphere_count=vol2.num_more_than(1);
	char filename[]="domain.raw";
	vol2.save(filename);
	
	// quick test of vertices, followed by test of trilinear inversion
	vertices pts(1000);
	pts.fill_rand();
	double x2[3];
	int ind;
	double err;
	for (unsigned int i=0;i<pts.get_size();i++) {
		pts.get_vertex(i,x);
		ind=ifs1.find_domain_and_invert(x,y);
		if (y[0]<0.0 || y[0]>1.0 || y[1]<0.0 || y[1]>1.0 || y[2]<0.0 || y[2]>1.0) printf("%f,%f,%f\n",y[0],y[1],y[2]);
		ifs1.apply_fn(ind,y,x2);
		err=sqrt((x[0]-x2[0])*(x[0]-x2[0])+(x[1]-x2[1])*(x[1]-x2[1])+(x[2]-x2[2])*(x[2]-x2[2]));
		if (err>1.0e-6) printf("y: %f,%f,%f err: %f\n",y[0],y[1],y[2],err);
	}
	
	// quick test of deterministic, (again transformation is identity)
	vertices pts2(1000);
	deterministic(ifs1,&pts,ifs1,&pts2);
	double toterr=0.0;
	for (unsigned int i=0;i<pts.get_size();i++) {
		pts.get_vertex(i,x);
		pts2.get_vertex(i,x2);
		err=sqrt((x[0]-x2[0])*(x[0]-x2[0])+(x[1]-x2[1])*(x[1]-x2[1])+(x[2]-x2[2])*(x[2]-x2[2]));
		toterr+=err;
	}
	printf("err in identity deterministic transform: %f\n",toterr);
	
	
	
	
	
	
	
	printf("\nNow some proper testing of chaos algorithms:\n\n");
	
	// quick test of chaos, (note transformation here is identity)
	vol.fill(0);
	clock_t t=clock();
	int mult=2;
	chaos(ifs1,&vol2,ifs1,&vol,mult);
	t=clock()-t;
	printf("Time for chaos: %f\n",(float)t/CLOCKS_PER_SEC);
	printf("\tits per second: ~%d\n",(int) ((float) mult*vol.get_size()/((float) t/CLOCKS_PER_SEC)));
	sum=vol.num_non_zero();
	printf("%d of expected %d\n",sum,(int) (vol.get_size()));
	sum=vol.num_more_than(1);
	//printf("%d of expected ~%d\n",sum,(int) (0.3*0.3*0.3*4.0/3.0*3.14159*vol.get_size()));
	printf("%d of expected ~%d\n",sum,sphere_count);
	char filename2[]="target.raw";
	vol.save(filename2);
	
	
	
	vol.fill(0);
	t=clock();
	mult=2;
	pure_chaos(ifs1,&vol2,ifs1,&vol,mult);
	t=clock()-t;
	printf("Time for pure_chaos: %f\n",(float)t/CLOCKS_PER_SEC);
	printf("\tits per second: ~%d\n",(int) ((float) mult*vol.get_size()/((float) t/CLOCKS_PER_SEC)));
	sum=vol.num_non_zero();
	printf("%d of expected %d\n",sum,(int) (vol.get_size()));
	sum=vol.num_more_than(1);
	printf("%d of expected ~%d\n",sum,sphere_count);
	
	
	
	
	vol.fill(0);
	//double omp_wt_t=omp_get_wtime();//t=clock();
	struct timeval tp;
	double sec,usec,start,end;
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	mult=2;
	unsigned int len=db_chaos_parallel(ifs1,&vol2,ifs1,&vol,mult);
	//omp_wt_t=(omp_get_wtime()-omp_wt_t)/omp_get_wtick();//t=clock()-t;
	//printf("Time for db_chaos_parallel: %f\n",(float)t/CLOCKS_PER_SEC);
	//printf("\tits per second: ~%d\n",(int) ((float) len/((float) t/CLOCKS_PER_SEC)));
	//printf("Time for db_chaos_parallel: %f\n",(float)omp_wt_t);
	//printf("\tits per second: ~%d\n",(int) ((float) len/((float) omp_wt_t)));
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
	
	
	
	
	vol.fill(0);
	t=clock();
	mult=2;
	len=db_chaos(ifs1,&vol2,ifs1,&vol,mult);
	t=clock()-t;
	printf("Time for db_chaos: %f\n",(float)t/CLOCKS_PER_SEC);
	printf("\tits per second: ~%d\n",(int) ((float) len/((float) t/CLOCKS_PER_SEC)));
	sum=vol.num_non_zero();
	printf("%d of expected %d\n",sum,(int) (vol.get_size()));
	sum=vol.num_more_than(1);
	printf("%d of expected ~%d\n",sum,sphere_count);
	
	
	
	
	
	vol.fill(0);
	t=clock();
	mult=2;
	len=original_chaos(ifs1,&vol2,ifs1,&vol,mult);
	t=clock()-t;
	printf("Time for original chaos: %f\n",(float)t/CLOCKS_PER_SEC);
	printf("\tits per second: ~%d\n",(int) ((float) len/((float) t/CLOCKS_PER_SEC)));
	sum=vol.num_non_zero();
	printf("%d of expected %d\n",sum,(int) (vol.get_size()));
	sum=vol.num_more_than(1);
	printf("%d of expected ~%d\n",sum,sphere_count);
	
	
	
	
	
	printf("\ntests completed\n");
	
	return 0;
	
}