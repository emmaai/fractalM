//
//  homeo_test.cpp
//
//
//  Created by Brendan Harding on 28/08/13.
//
//

#include "db_chaos_3d_parallel_8tetra.h"
#include<ctime>
#include"omp.h"
#include<sys/time.h>

int LOGGING=1;


int main(){
	
	// Give full path to the raw volume to transform
	char raw_volume_filename[]="../mt_gambier_8bit.pvl.nc.001";
	//"/short/fh0/tbh251/vdata/AM/MtGambier_poly/tomo2048.nc/cropped.raw";
	
	// Give the full path for the transformed volume filename
	char transform_filename[]="../transform.raw";
	//"/short/fh0/tbh251/vdata/AM/MtGambier_poly/tomo2048.nc/transform_cropped.raw";
	
	if (LOGGING>0) printf("Opening volume files...\n");
	
	// load the left (colour stealing) volume
	large_volume left_vol(0,0,0);
	left_vol.load(raw_volume_filename);
	
	// optional, compute how many point more than some fixed number
	unsigned char iso=100; 
	uint64_t sum_lv=left_vol.num_more_than(iso);
	
	// get the dimensions
	unsigned int dimensions[3];
	dimensions[0]=left_vol.get_dep();
	dimensions[1]=left_vol.get_hei();
	dimensions[2]=left_vol.get_wid();
	
	// initialise the right (target) volume
	large_volume right_vol(dimensions[2],dimensions[1],dimensions[0]);
	// Note: all entries are set to 0 when it is allocated.
	
	if (LOGGING>0) printf("Setting up IFS's...\n");

	// Allocate IFSs and coordinate variables
	affine fn;
	affineIFS left_ifs(8);
	affineIFS right_ifs(8);
	double A[3],B[3],C[3],D[3];
	
	int embedding_mode=4;
	// 0 for equilateral tetrahedron (default)
	// 1 for tetrahedron touching faces of cube
	// 2 for a large tetrahedron (almost) containing the cube
	// 3 for a tetra which is copied 6 times to fill the cube
	// 4 for a tetra which is copied 5 times to fill the cube
	int map_mode=0;
	// 0 for the 2-variable family (default)
	// 1 for the 4-variable family
	double param_l=0.45;
	double param_r=0.55;
	
	A[0]=0.0;
	A[1]=0.0;
	A[2]=0.0;
	B[0]=1.0;
	B[1]=0.0;
	B[2]=0.0;
	C[0]=0.5;
	C[1]=sqrt(0.75);
	C[2]=0.0;
	D[0]=0.5;
	D[1]=sqrt(3.0)/6.0;
	D[2]=sqrt(2.0/3.0);	
	if (embedding_mode==1) {
		C[0]=0.5;
		C[1]=1.0;
		C[2]=0.0;
		D[0]=0.5;
		D[1]=0.375;
		D[2]=1.0;
	} else if (embedding_mode==2) {
		A[0]=-1.0;
		A[1]=-0.5;
		A[2]=0.0;
		B[0]=2.0;
		B[1]=-0.5;
		B[2]=0.0;
		C[0]=0.5;
		C[1]=0.5*(3.0*sqrt(3.0)-1.0);
		C[2]=0.0;
		D[0]=0.5;
		D[1]=0.5*(sqrt(3.0)-1.0);	
		D[2]=sqrt(6.0);  	
	} else if (embedding_mode==3) {
		A[0]=0.0;
		A[1]=0.0;
		A[2]=0.0;
		B[0]=1.0;
		B[1]=0.0;
		B[2]=0.0;
		C[0]=0.0;
		C[1]=1.0;
		C[2]=0.0;
		D[0]=0.0;
		D[1]=0.0;
		D[2]=1.0;
	} else if (embedding_mode==4) {
		A[0]=0.0;
		A[1]=0.0;
		A[2]=0.0;
		B[0]=1.0;
		B[1]=0.0;
		B[2]=0.0;
		C[0]=1.0;
		C[1]=1.0;
		C[2]=0.0;
		D[0]=0.0;
		D[1]=0.0;
		D[2]=1.0;
	};
	
	// set up the left IFS
	double alphaAB=param_l;
	double alphaAC=0.5;
	double alphaAD=0.5;
	double alphaBC=0.5;
	double alphaBD=0.5;
	double alphaCD=1.0-param_l;
	if (map_mode==1) {
		alphaAC=1.0-param_l;
		alphaBD=param_l;
	}
	
	double AB[3],AC[3],AD[3],BC[3],BD[3],CD[3];
	for (int i=0;i<3;i++) {
		AB[i]=A[i]+alphaAB*(B[i]-A[i]);
		AC[i]=A[i]+alphaAC*(C[i]-A[i]);
		AD[i]=A[i]+alphaAD*(D[i]-A[i]);
		BC[i]=B[i]+alphaBC*(C[i]-B[i]);
		BD[i]=B[i]+alphaBD*(D[i]-B[i]);
		CD[i]=C[i]+alphaCD*(D[i]-C[i]);
	}
	
	fn.set_from_4pt_mapping(A,B,C,D,A ,AB,AC,AD);
	left_ifs.set_fn(0,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,BD,B );
	left_ifs.set_fn(1,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,AC,C );
	left_ifs.set_fn(2,fn);
	fn.set_from_4pt_mapping(A,B,C,D,D ,CD,BD,AD);
	left_ifs.set_fn(3,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,AC,AD);
	left_ifs.set_fn(4,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,BD,AD);
	left_ifs.set_fn(5,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,AC,AD);
	left_ifs.set_fn(6,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,BD,AD);
	left_ifs.set_fn(7,fn);
	
	// Now set up the right IFS
	double betaAB=0.5;
	double betaAC=param_r;
	double betaAD=0.5;
	double betaBC=0.5;
	double betaBD=1.0-param_r;
	double betaCD=0.5;
	if (map_mode==2) {
		betaAB=1.0-param_r;
		betaCD=param_r;
	}
	
	for (int i=0;i<3;i++) {
		AB[i]=A[i]+betaAB*(B[i]-A[i]);
		AC[i]=A[i]+betaAC*(C[i]-A[i]);
		AD[i]=A[i]+betaAD*(D[i]-A[i]);
		BC[i]=B[i]+betaBC*(C[i]-B[i]);
		BD[i]=B[i]+betaBD*(D[i]-B[i]);
		CD[i]=C[i]+betaCD*(D[i]-C[i]);
	}
	
	fn.set_from_4pt_mapping(A,B,C,D,A ,AB,AC,AD);
	right_ifs.set_fn(0,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,BD,B );
	right_ifs.set_fn(1,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,AC,C );
	right_ifs.set_fn(2,fn);
	fn.set_from_4pt_mapping(A,B,C,D,D ,CD,BD,AD);
	right_ifs.set_fn(3,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,AC,AD);
	right_ifs.set_fn(4,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,AB,BD,AD);
	right_ifs.set_fn(5,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,AC,AD);
	right_ifs.set_fn(6,fn);
	fn.set_from_4pt_mapping(A,B,C,D,BC,CD,BD,AD);
	right_ifs.set_fn(7,fn);
	
	if (LOGGING>0) printf("Applying transformation...\n");
	
	// Set the iteration multiplier
	// mult=2 will result in a length ? sequence for most large volumes
	//     this takes approximately ? minutes with 16 threads
	//     the length ? sequence typically fills ??%
	//     this is good for an initial test
	// mult=4 will result in a length  sequence for most large volumes
	//     this takes approximately ?? minutes with 16 threads
	//     the length ? sequence typically fills ??%
	//     this is good for a high quality result after an initial test
	int mult=4;
	// the other embedding modes need less iterations
	if (embedding_mode==3 || embedding_mode==4) mult=2;
	
	struct timeval tp;
	double sec,usec,start,end;
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	start=sec+usec;
	uint64_t len;
	if (embedding_mode==2) {
		len=db_chaos_parallel_8tetra_large_safe(left_ifs,&left_vol,right_ifs,&right_vol,mult);
	} else if (embedding_mode==3) {
		len=db_chaos_parallel_large_5x8tetra(left_ifs,&left_vol,right_ifs,&right_vol,mult);
	} else if (embedding_mode==4) {
		len=db_chaos_parallel_large_6x8tetra_alt(left_ifs,&left_vol,right_ifs,&right_vol,mult);
	} else {
		len=db_chaos_parallel_8tetra_large(left_ifs,&left_vol,right_ifs,&right_vol,mult);
	};
	gettimeofday(&tp,NULL);
	sec=static_cast<double>(tp.tv_sec);
	usec=static_cast<double>(tp.tv_usec)/1E6;
	end=sec+usec;
	printf("Time for db_chaos_parallel: %f\n",end-start);
	printf("\tits per second: ~%d\n",(int) ((float) len/(end-start)));
	
	// optional, compare number of entries more than fixed number with left_vol
	uint64_t sum_rv=right_vol.num_more_than(iso);
	printf("Number of elements more than %u\n\tin left_vol: %u\n\tin right_vol: %u\n",(unsigned int) iso,(unsigned int) sum_lv,(unsigned int) sum_rv);
	
	if (LOGGING>0) printf("Writing transformed data to file...\n");

	right_vol.save(transform_filename);
	
	if (LOGGING>0) printf("Completed\n");

	return 0;

};
