//
//  db_chaos_3d_parallel.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _db_chaos_3d_parallel_h

#include"trilinear_class.h"
#include"db_class.h"
#include"omp.h"

// Uses OpenMP to parllelise the debruijn loop
// number of threads should be power of 2 of at most 8, e.g. one of 1,2,4,8

uint64_t db_chaos_parallel(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,int64_t its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const int64_t maxits=its_mult*vol2->get_size();
	int dbl=0;
	uint64_t temp=maxits;
	uint64_t temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(uint64_t) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const uint64_t its=temp2;
	#pragma omp parallel
	{
		trilinearIFS ifst1=ifs1,ifst2=ifs2;
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
			const uint64_t pits=its/nthreads;
			const unsigned int wid1=vol1->get_wid();
			const unsigned int hei1=vol1->get_hei();
			const unsigned int wid2=vol2->get_wid();
			const unsigned int hei2=vol2->get_hei();
			const unsigned int wid1m1=wid1-1;
			const unsigned int hei1m1=hei1-1;
			const unsigned int dep1m1=vol1->get_dep()-1;
			const unsigned int wid2m1=wid2-1;
			const unsigned int hei2m1=hei2-1;
			const unsigned int dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (uint64_t it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			for (uint64_t it=0;it<pits;it+=2) {
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
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((uint64_t) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(uint64_t) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				vol2->set_dat_from_ind(vol1->get_dat_from_ind((uint64_t) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(uint64_t) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				/*
				unsigned char dat1,dat2;
				dat1=vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]);
				dat2=vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]);
				if (dat1>vol2->get_dat_from_ind((iy2[2]*hei2+iy2[1])*wid2+iy2[0])) vol2->set_dat_from_ind(dat1,(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				if (dat2>vol2->get_dat_from_ind((ix2[2]*hei2+ix2[1])*wid2+ix2[0])) vol2->set_dat_from_ind(dat2,(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				 */
			}
		}
	} // end #pragma omp parallel
	return its;
}


// use of special large volume class for really big volumes on raijin
uint64_t db_chaos_parallel_large(trilinearIFS ifs1,large_volume* vol1,trilinearIFS ifs2,large_volume* vol2,int64_t its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0 || ifs1.len()!=8) {
		printf("ERROR: db_chaos_parallel: both IFSs must have the same length=8\n");
		return 0;
	}
	//const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const int64_t maxits=its_mult*vol2->get_size();
	int dbl=0;
	uint64_t temp=maxits;
	uint64_t temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	if (dbl<5) {dbl=5;temp2=32768;};
	if (dbl>14) {dbl=14;temp2=(uint64_t) 4096*1073741824;};
	printf("Sequence length: %d\n",dbl);
	const uint64_t its=temp2;
	#pragma omp parallel
	{
		trilinearIFS ifst1=ifs1,ifst2=ifs2;
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
			const uint64_t pits=its/nthreads;
			const unsigned int wid1=vol1->get_wid();
			const unsigned int hei1=vol1->get_hei();
			const unsigned int wid2=vol2->get_wid();
			const unsigned int hei2=vol2->get_hei();
			const unsigned int wid1m1=wid1-1;
			const unsigned int hei1m1=hei1-1;
			const unsigned int dep1m1=vol1->get_dep()-1;
			const unsigned int wid2m1=wid2-1;
			const unsigned int hei2m1=hei2-1;
			const unsigned int dep2m1=vol2->get_dep()-1;
			unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
			int ran1,ran2;
			double x1[3],y1[3],x2[3],y2[3];
			x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
			x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
			for (uint64_t it=32;it<46;it+=2) {
				ifst1.apply_fn(state_vec[it],x1,y1);
				ifst1.apply_fn(state_vec[it+1],y1,x1);
				ifst2.apply_fn(state_vec[it],x2,y2);
				ifst2.apply_fn(state_vec[it+1],y2,x2);
			}
			for (uint64_t it=0;it<pits;it+=2) {
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
				vol2->set_dat_from_coord(vol1->get_dat_from_coord(iy1[0],iy1[1],iy1[2]),iy2[0],iy2[1],iy2[2]);
				vol2->set_dat_from_coord(vol1->get_dat_from_coord(ix1[0],ix1[1],ix1[2]),ix2[0],ix2[1],ix2[2]);
				//vol2->set_dat_from_ind(vol1->get_dat_from_ind((uint64_t) (iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(uint64_t) (iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				//vol2->set_dat_from_ind(vol1->get_dat_from_ind((uint64_t) (ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(uint64_t) (ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				/*
				unsigned char dat1,dat2;
				dat1=vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]);
				dat2=vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]);
				if (dat1>vol2->get_dat_from_ind((iy2[2]*hei2+iy2[1])*wid2+iy2[0])) vol2->set_dat_from_ind(dat1,(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
				if (dat2>vol2->get_dat_from_ind((ix2[2]*hei2+ix2[1])*wid2+ix2[0])) vol2->set_dat_from_ind(dat2,(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
				 */
			}
		}
	} // end #pragma omp parallel
	return its;
}


#define _db_chaos_3d_parallel_h



#endif
