//
//  db_chaos_3d_parallel_8tetra.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#include<stdio.h>
#include<string.h>
#include"affine_class.h"
#include"db_class.h"
#include"db_lookup_b8_l5_14_t32.h" // debruijn lookup table
#include"omp.h"

// Uses OpenMP to parllelise the debruijn loop
// number of threads should be power of 2 of at most 8, e.g. one of 1,2,4,8

// The first two methods can be used if the tetrahedron is defined within the unit cube. Otherwise the third or fourth method needs to be used.

unsigned long db_chaos_parallel_8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned long maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned long temp=maxits;
	unsigned long temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(unsigned long) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const unsigned long its=temp2;
	#pragma omp parallel
	{
		affineIFS ifst1=ifs1,ifst2=ifs2;
		int nthreads=omp_get_num_threads();
		int th_id=omp_get_thread_num();
		if (th_id==0) printf("Num OMP threads: %d\n",nthreads);
		if (nthreads==1 || nthreads==2 || nthreads==4 || nthreads==8 || nthreads==16 || nthreads==32) {
			//printf("%d\n",th_id);
			int sm=32/nthreads;
			int th_st=sm*th_id;
			int state_vec[46];
			int offset=46*(32*(dbl-5)+th_st);
			for (int i=0;i<46;i++) state_vec[i]=db8_lookup14[offset+i];
			deBruijn db(8,dbl);
			db.set_state(state_vec);
			const unsigned long pits=its/nthreads;
			const unsigned long wid1=vol1->get_wid();
			const unsigned long hei1=vol1->get_hei();
			const unsigned long wid2=vol2->get_wid();
			const unsigned long hei2=vol2->get_hei();
			const unsigned long wid1m1=wid1-1;
			const unsigned long hei1m1=hei1-1;
			const unsigned long dep1m1=vol1->get_dep()-1;
			const unsigned long wid2m1=wid2-1;
			const unsigned long hei2m1=hei2-1;
			const unsigned long dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (unsigned long it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			for (unsigned long it=0;it<pits;it+=2) {
				ran1=db.next();
				ran2=db.next();
				ifst1.apply_fn(ran1,x1,y1);
				ifst2.apply_fn(ran1,x2,y2);
				ifst1.apply_fn(ran2,y1,x1);
				ifst2.apply_fn(ran2,y2,x2);
				iy1[0]=0.5+y1[0]*wid1m1;
				ix1[0]=0.5+x1[0]*wid1m1;
				iy1[1]=0.5+y1[1]*hei1m1;
				ix1[1]=0.5+x1[1]*hei1m1;
				iy1[2]=0.5+y1[2]*dep1m1;
				ix1[2]=0.5+x1[2]*dep1m1;
				iy2[0]=0.5+y2[0]*wid2m1;
				ix2[0]=0.5+x2[0]*wid2m1;
				iy2[1]=0.5+y2[1]*hei2m1;
				ix2[1]=0.5+x2[1]*hei2m1;
				iy2[2]=0.5+y2[2]*dep2m1;
				ix2[2]=0.5+x2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
			}
		}
	} // end #pragma omp parallel
	return its;
}

unsigned long db_chaos_parallel_8tetra_safe(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned long maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned long temp=maxits;
	unsigned long temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(unsigned long) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const unsigned long its=temp2;
	#pragma omp parallel
	{
		affineIFS ifst1=ifs1,ifst2=ifs2;
		int nthreads=omp_get_num_threads();
		int th_id=omp_get_thread_num();
		if (th_id==0) printf("Num OMP threads: %d\n",nthreads);
		if (nthreads==1 || nthreads==2 || nthreads==4 || nthreads==8 || nthreads==16 || nthreads==32) {
			//printf("%d\n",th_id);
			int sm=32/nthreads;
			int th_st=sm*th_id;
			int state_vec[46];
			int offset=46*(32*(dbl-5)+th_st);
			for (int i=0;i<46;i++) state_vec[i]=db8_lookup14[offset+i];
			deBruijn db(8,dbl);
			db.set_state(state_vec);
			const unsigned long pits=its/nthreads;
			const unsigned long wid1=vol1->get_wid();
			const unsigned long hei1=vol1->get_hei();
			const unsigned long wid2=vol2->get_wid();
			const unsigned long hei2=vol2->get_hei();
			const unsigned long wid1m1=wid1-1;
			const unsigned long hei1m1=hei1-1;
			const unsigned long dep1m1=vol1->get_dep()-1;
			const unsigned long wid2m1=wid2-1;
			const unsigned long hei2m1=hei2-1;
			const unsigned long dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (unsigned long it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			for (unsigned long it=0;it<pits;it+=2) {
				ran1=db.next();
				ran2=db.next();
				ifst1.apply_fn(ran1,x1,y1);
				ifst2.apply_fn(ran1,x2,y2);
				ifst1.apply_fn(ran2,y1,x1);
				ifst2.apply_fn(ran2,y2,x2);
				if (y1[0]>=0.0 && y1[1]>=0.0 && y1[2]>=0.0 && y1[0]<=1.0 && y1[1]<=1.0 && y1[2]<=1.0 && y2[0]>=0.0 && y2[1]>=0.0 && y2[2]>=0.0 && y2[0]<=1.0 && y2[1]<=1.0 && y2[2]<=1.0) {
					iy1[0]=0.5+y1[0]*wid1m1;
					iy1[1]=0.5+y1[1]*hei1m1;
					iy1[2]=0.5+y1[2]*dep1m1;
					iy2[0]=0.5+y2[0]*wid2m1;
					iy2[1]=0.5+y2[1]*hei2m1;
					iy2[2]=0.5+y2[2]*dep2m1;
					vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				};
				if (x1[0]>=0.0 && x1[1]>=0.0 && x1[2]>=0.0 && x1[0]<=1.0 && x1[1]<=1.0 && x1[2]<=1.0 && x2[0]>=0.0 && x2[1]>=0.0 && x2[2]>=0.0 && x2[0]<=1.0 && x2[1]<=1.0 && x2[2]<=1.0) {
					ix1[0]=0.5+x1[0]*wid1m1;
					ix1[1]=0.5+x1[1]*hei1m1;
					ix1[2]=0.5+x1[2]*dep1m1;
					ix2[0]=0.5+x2[0]*wid2m1;
					ix2[1]=0.5+x2[1]*hei2m1;
					ix2[2]=0.5+x2[2]*dep2m1;
					vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				};
			}
		}
	} // end #pragma omp parallel
	return its;
}

// This is designed for the case where the tetrahedron is
// (0,0,0), (1,0,0), (0,1,0), (0,0,1)
// which we then map to 5 other tetrahedrons to fill the cube
// (it is also possible to do this with only 4 tetrahedron)
// (it is also possible to tile the cube with 6 congruent tetrahedra,
//   but noe of them are the canonical one above)
unsigned long db_chaos_parallel_large_6x8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned long maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned long temp=maxits;
	unsigned long temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(unsigned long) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const unsigned long its=temp2;
	#pragma omp parallel
	{
		affineIFS ifst1=ifs1,ifst2=ifs2;
		affine tetra1,tetra2,tetra3,tetra4,tetra5;
		double A[3]={0.0,0.0,0.0};
		double B[3]={1.0,0.0,0.0};
		double C[3]={0.0,1.0,0.0};
		double D[3]={0.0,0.0,1.0};
		double a[3]={0.0,1.0,1.0};
		double b[3]={1.0,0.0,0.0};
		double c[3]={0.0,1.0,0.0};
		double d[3]={0.0,0.0,1.0};
		tetra1.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		c[0]=1.0;c[1]=0.0;c[2]=1.0;
		tetra2.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		d[0]=1.0;d[1]=1.0;d[2]=1.0;
		tetra3.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		c[0]=0.0;c[1]=1.0;c[2]=0.0;
		tetra4.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		a[0]=1.0;a[1]=1.0;a[2]=0.0;
		tetra5.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		int nthreads=omp_get_num_threads();
		int th_id=omp_get_thread_num();
		if (th_id==0) printf("Num OMP threads: %d\n",nthreads);
		if (nthreads==1 || nthreads==2 || nthreads==4 || nthreads==8 || nthreads==16 || nthreads==32) {
			//printf("%d\n",th_id);
			int sm=32/nthreads;
			int th_st=sm*th_id;
			int state_vec[46];
			int offset=46*(32*(dbl-5)+th_st);
			for (int i=0;i<46;i++) state_vec[i]=db8_lookup14[offset+i];
			deBruijn db(8,dbl);
			db.set_state(state_vec);
			const unsigned long pits=its/nthreads;
			const unsigned long wid1=vol1->get_wid();
			const unsigned long hei1=vol1->get_hei();
			const unsigned long wid2=vol2->get_wid();
			const unsigned long hei2=vol2->get_hei();
			const unsigned long wid1m1=wid1-1;
			const unsigned long hei1m1=hei1-1;
			const unsigned long dep1m1=vol1->get_dep()-1;
			const unsigned long wid2m1=wid2-1;
			const unsigned long hei2m1=hei2-1;
			const unsigned long dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3],t1[3],t2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (unsigned long it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			//
			// A manual loop unroll
			for (unsigned long it=0;it<pits;it+=2) {
				ran1=db.next();
				ran2=db.next();
				ifst1.apply_fn(ran1,x1,y1);
				ifst2.apply_fn(ran1,x2,y2);
				ifst1.apply_fn(ran2,y1,x1);
				ifst2.apply_fn(ran2,y2,x2);
				iy1[0]=0.5+y1[0]*wid1m1;
				iy1[1]=0.5+y1[1]*hei1m1;
				iy1[2]=0.5+y1[2]*dep1m1;
				iy2[0]=0.5+y2[0]*wid2m1;
				iy2[1]=0.5+y2[1]*hei2m1;
				iy2[2]=0.5+y2[2]*dep2m1;
				printf("get index is %d, %d, %d\n", y1[0], y1[1], y1[2]);
				printf("set index is %d, %d, %d\n", y2[0], y2[1], y2[2]);
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				// now the five mappings
				tetra1.apply(y1,t1);
				tetra1.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra2.apply(y1,t1);
				tetra2.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra3.apply(y1,t1);
				tetra3.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra4.apply(y1,t1);
				tetra4.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra5.apply(y1,t1);
				tetra5.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				// now the second map
				ix1[0]=0.5+x1[0]*wid1m1;
				ix1[1]=0.5+x1[1]*hei1m1;
				ix1[2]=0.5+x1[2]*dep1m1;
				ix2[0]=0.5+x2[0]*wid2m1;
				ix2[1]=0.5+x2[1]*hei2m1;
				ix2[2]=0.5+x2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				// now the five mappings
				tetra1.apply(x1,t1);
				tetra1.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra2.apply(x1,t1);
				tetra2.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra3.apply(x1,t1);
				tetra3.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra4.apply(x1,t1);
				tetra4.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra5.apply(x1,t1);
				tetra5.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
			}
		}
	} // end #pragma omp parallel
	return its*6;
}






// This uses the 6 congruent tetra
// the original tetrahedon should be
// (0,0,0), (1,0,0), (1,1,0), (0,0,1)
unsigned long db_chaos_parallel_large_6x8tetra_alt(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned long maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned long temp=maxits;
	unsigned long temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(unsigned long) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const unsigned long its=temp2;
	#pragma omp parallel
	{
		affineIFS ifst1=ifs1,ifst2=ifs2;
		affine tetra1,tetra2,tetra3,tetra4,tetra5;
		double A[3]={0.0,0.0,0.0};
		double B[3]={1.0,0.0,0.0};
		double C[3]={1.0,1.0,0.0};
		double D[3]={0.0,0.0,1.0};
		double a[3]={1.0,0.0,1.0};
		double b[3]={1.0,0.0,0.0};
		double c[3]={1.0,1.0,0.0};
		double d[3]={0.0,0.0,1.0};
		tetra1.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		b[0]=1.0;b[1]=1.0;b[2]=1.0;
		tetra2.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		a[0]=0.0;a[1]=1.0;a[2]=1.0;
		tetra3.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		b[0]=0.0;b[1]=1.0;b[2]=0.0;
		tetra4.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		a[0]=0.0;a[1]=0.0;a[2]=0.0;
		tetra5.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		int nthreads=omp_get_num_threads();
		int th_id=omp_get_thread_num();
		if (th_id==0) printf("Num OMP threads: %d\n",nthreads);
		if (nthreads==1 || nthreads==2 || nthreads==4 || nthreads==8 || nthreads==16 || nthreads==32) {
			//printf("%d\n",th_id);
			int sm=32/nthreads;
			int th_st=sm*th_id;
			int state_vec[46];
			int offset=46*(32*(dbl-5)+th_st);
			for (int i=0;i<46;i++) state_vec[i]=db8_lookup14[offset+i];
			deBruijn db(8,dbl);
			db.set_state(state_vec);
			const unsigned long pits=its/nthreads;
			const unsigned long wid1=vol1->get_wid();
			const unsigned long hei1=vol1->get_hei();
			const unsigned long wid2=vol2->get_wid();
			const unsigned long hei2=vol2->get_hei();
			const unsigned long wid1m1=wid1-1;
			const unsigned long hei1m1=hei1-1;
			const unsigned long dep1m1=vol1->get_dep()-1;
			const unsigned long wid2m1=wid2-1;
			const unsigned long hei2m1=hei2-1;
			const unsigned long dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3],t1[3],t2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (unsigned long it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			//
			// A manual loop unroll
			for (unsigned long it=0;it<pits;it+=2) {
				ran1=db.next();
				ran2=db.next();
				ifst1.apply_fn(ran1,x1,y1);
				ifst2.apply_fn(ran1,x2,y2);
				ifst1.apply_fn(ran2,y1,x1);
				ifst2.apply_fn(ran2,y2,x2);
				if (y1[0]>=0.0 && y1[1]>=0.0 && y1[2]>=0.0 && y1[0]<=1.0 && y1[1]<=1.0 && y1[2]<=1.0 && y2[0]>=0.0 && y2[1]>=0.0 && y2[2]>=0.0 && y2[0]<=1.0 && y2[1]<=1.0 && y2[2]<=1.0) {
				iy1[0]=0.5+y1[0]*wid1m1;
				iy1[1]=0.5+y1[1]*hei1m1;
				iy1[2]=0.5+y1[2]*dep1m1;
				iy2[0]=0.5+y2[0]*wid2m1;
				iy2[1]=0.5+y2[1]*hei2m1;
				iy2[2]=0.5+y2[2]*dep2m1;

				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				// now the five mappings
				tetra1.apply(y1,t1);
				tetra1.apply(y2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				tetra2.apply(y1,t1);
				tetra2.apply(y2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				tetra3.apply(y1,t1);
				tetra3.apply(y2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				tetra4.apply(y1,t1);
				tetra4.apply(y2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				tetra5.apply(y1,t1);
				tetra5.apply(y2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				}
				// now the second map
				if (x1[0]>=0.0 && x1[1]>=0.0 && x1[2]>=0.0 && x1[0]<=1.0 && x1[1]<=1.0 && x1[2]<=1.0 && x2[0]>=0.0 && x2[1]>=0.0 && x2[2]>=0.0 && x2[0]<=1.0 && x2[1]<=1.0 && x2[2]<=1.0) {
				ix1[0]=0.5+x1[0]*wid1m1;
				ix1[1]=0.5+x1[1]*hei1m1;
				ix1[2]=0.5+x1[2]*dep1m1;
				ix2[0]=0.5+x2[0]*wid2m1;
				ix2[1]=0.5+x2[1]*hei2m1;
				ix2[2]=0.5+x2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
				// now the five mappings
				tetra1.apply(x1,t1);
				tetra1.apply(x2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
				tetra2.apply(x1,t1);
				tetra2.apply(x2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
				tetra3.apply(x1,t1);
				tetra3.apply(x2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
				tetra4.apply(x1,t1);
				tetra4.apply(x2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
				tetra5.apply(x1,t1);
				tetra5.apply(x2,t2);
				if (t1[0]>=0.0 && t1[1]>=0.0 && t1[2]>=0.0 && t1[0]<=1.0 && t1[1]<=1.0 && t1[2]<=1.0 && t2[0]>=0.0 && t2[1]>=0.0 && t2[2]>=0.0 && t2[0]<=1.0 && t2[1]<=1.0 && t2[2]<=1.0) {
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				}
			}
		}
	} // end #pragma omp parallel
	return its*6;
}

// This is designed for the case where the tetrahedron is
// (0,0,0), (1,0,0), (0,1,0), (0,0,1)
// which we then map to 4 other tetrahedrons to fill the cube
unsigned long db_chaos_parallel_large_5x8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned long maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned long temp=maxits;
	unsigned long temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(unsigned long) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const unsigned long its=temp2;
	#pragma omp parallel
	{
		affineIFS ifst1=ifs1,ifst2=ifs2;
		affine tetra1,tetra2,tetra3,tetra4;
		double A[3]={0.0,0.0,0.0};
		double B[3]={1.0,0.0,0.0};
		double C[3]={0.0,1.0,0.0};
		double D[3]={0.0,0.0,1.0};
		double a[3]={1.0,1.0,1.0};
		double b[3]={1.0,0.0,0.0};
		double c[3]={0.0,1.0,0.0};
		double d[3]={1.0,1.0,0.0};
		tetra1.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		c[0]=1.0;c[1]=0.0;c[2]=1.0;
		d[0]=0.0;d[1]=0.0;d[2]=1.0;
		tetra2.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		b[0]=0.0;b[1]=1.0;b[2]=1.0;
		c[0]=0.0;c[1]=1.0;c[2]=0.0;
		tetra3.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		b[0]=1.0;b[1]=0.0;b[2]=0.0;
		tetra4.set_from_4pt_mapping(A,B,C,D,a,b,c,d);
		int nthreads=omp_get_num_threads();
		int th_id=omp_get_thread_num();
		if (th_id==0) printf("Num OMP threads: %d\n",nthreads);
		if (nthreads==1 || nthreads==2 || nthreads==4 || nthreads==8 || nthreads==16 || nthreads==32) {
			//printf("%d\n",th_id);
			int sm=32/nthreads;
			int th_st=sm*th_id;
			int state_vec[46];
			int offset=46*(32*(dbl-5)+th_st);
			for (int i=0;i<46;i++) state_vec[i]=db8_lookup14[offset+i];
			deBruijn db(8,dbl);
			db.set_state(state_vec);
			const unsigned long pits=its/nthreads;
			const unsigned long wid1=vol1->get_wid();
			const unsigned long hei1=vol1->get_hei();
			const unsigned long wid2=vol2->get_wid();
			const unsigned long hei2=vol2->get_hei();
			const unsigned long wid1m1=wid1-1;
			const unsigned long hei1m1=hei1-1;
			const unsigned long dep1m1=vol1->get_dep()-1;
			const unsigned long wid2m1=wid2-1;
			const unsigned long hei2m1=hei2-1;
			const unsigned long dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3],t1[3],t2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (unsigned long it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			//
			// A manual loop unroll
			for (unsigned long it=0;it<pits;it+=2) {
				ran1=db.next();
				ran2=db.next();
				ifst1.apply_fn(ran1,x1,y1);
				ifst2.apply_fn(ran1,x2,y2);
				ifst1.apply_fn(ran2,y1,x1);
				ifst2.apply_fn(ran2,y2,x2);
				iy1[0]=0.5+y1[0]*wid1m1;
				iy1[1]=0.5+y1[1]*hei1m1;
				iy1[2]=0.5+y1[2]*dep1m1;
				iy2[0]=0.5+y2[0]*wid2m1;
				iy2[1]=0.5+y2[1]*hei2m1;
				iy2[2]=0.5+y2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				// now the five mappings
				tetra1.apply(y1,t1);
				tetra1.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra2.apply(y1,t1);
				tetra2.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra3.apply(y1,t1);
				tetra3.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				tetra4.apply(y1,t1);
				tetra4.apply(y2,t2);
				iy1[0]=0.5+t1[0]*wid1m1;
				iy1[1]=0.5+t1[1]*hei1m1;
				iy1[2]=0.5+t1[2]*dep1m1;
				iy2[0]=0.5+t2[0]*wid2m1;
				iy2[1]=0.5+t2[1]*hei2m1;
				iy2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(unsigned long) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				// now the second map
				ix1[0]=0.5+x1[0]*wid1m1;
				ix1[1]=0.5+x1[1]*hei1m1;
				ix1[2]=0.5+x1[2]*dep1m1;
				ix2[0]=0.5+x2[0]*wid2m1;
				ix2[1]=0.5+x2[1]*hei2m1;
				ix2[2]=0.5+x2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				// now the five mappings
				tetra1.apply(x1,t1);
				tetra1.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra2.apply(x1,t1);
				tetra2.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra3.apply(x1,t1);
				tetra3.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				tetra4.apply(x1,t1);
				tetra4.apply(x2,t2);
				ix1[0]=0.5+t1[0]*wid1m1;
				ix1[1]=0.5+t1[1]*hei1m1;
				ix1[2]=0.5+t1[2]*dep1m1;
				ix2[0]=0.5+t2[0]*wid2m1;
				ix2[1]=0.5+t2[1]*hei2m1;
				ix2[2]=0.5+t2[2]*dep2m1;
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((unsigned long) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(unsigned long) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
			}
		}
	} // end #pragma omp parallel
	return its*5;
}
