// quick test on whether
// if (x>=0.0 && x<=1.0)
// or
// if (x*(1.0-x)>=0.0)
// is quicker
// The latter appears to be slightly faster,
// by about 20% on my mac (g++ -O3) for a single element
// but seems slightly worse when done on multiple elements


#include<ctime>
#include<sys/time.h>
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>


// Operators on 2 IFSs:
// chaos game transform (for volumetric data)
int main() {
	
	unsigned int its=100*1000*1000;
	double ran,arr[6];
	int sum;
	struct timeval tp;
	double sec,usec,start,end;
	
	printf("%d\n",RAND_MAX);
	
	
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		ran=-1.0+0.000000001*rand();
		sum++;
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time of control: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);

	
	
	srand(0);
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		ran=-1.0+0.000000001*rand();
		if (ran>=0.0 && ran<=1.0) {
			sum++;
		} else {
			sum--;
		}
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time two conditionals: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);
	
	
	
	srand(0);
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		ran=-1.0+0.000000001*rand();
		if (ran*(1.0-ran)>=0.0) {
			sum++;
		} else {
			sum--;
		}
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time complex conditionals: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);
	
	
	
	
	
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		arr[0]=-1.0+0.000000001*rand();
		arr[1]=-1.0+0.000000001*rand();
		arr[2]=-1.0+0.000000001*rand();
		arr[3]=-1.0+0.000000001*rand();
		arr[4]=-1.0+0.000000001*rand();
		arr[5]=-1.0+0.000000001*rand();
		sum++;
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time of control: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);
	
	
	
	srand(0);
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		arr[0]=-1.0+0.000000001*rand();
		arr[1]=-1.0+0.000000001*rand();
		arr[2]=-1.0+0.000000001*rand();
		arr[3]=-1.0+0.000000001*rand();
		arr[4]=-1.0+0.000000001*rand();
		arr[5]=-1.0+0.000000001*rand();
		if (arr[0]>=0.0 && arr[0]<=1.0 && arr[1]>=0.0 && arr[1]<=1.0 && arr[2]>=0.0 && arr[2]<=1.0 && arr[3]>=0.0 && arr[3]<=1.0 && arr[4]>=0.0 && arr[4]<=1.0 && arr[5]>=0.0 && arr[5]<=1.0) {
			sum++;
		} else {
			sum--;
		}
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time two conditionals: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);
	
	
	
	srand(0);
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	
	sum=0;
	for (unsigned int it=0;it<its;it++) {
		arr[0]=-1.0+0.000000001*rand();
		arr[1]=-1.0+0.000000001*rand();
		arr[2]=-1.0+0.000000001*rand();
		arr[3]=-1.0+0.000000001*rand();
		arr[4]=-1.0+0.000000001*rand();
		arr[5]=-1.0+0.000000001*rand();
		if (arr[0]*(1.0-arr[0])>=0 && arr[1]*(1.0-arr[1])>=0 && arr[2]*(1.0-arr[2])>=0 && arr[3]*(1.0-arr[3])>=0 && arr[4]*(1.0-arr[4])>=0 && arr[5]*(1.0-arr[5])>=0.0) {
			sum++;
		} else {
			sum--;
		}
	};
	
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time complex conditionals: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) its/(end-start)));
	printf("Sum: %d\n",sum);
	
	
	
	return 0;
}

