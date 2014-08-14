//
//  homeo_3d.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _homeo_3d_h

#include"trilinear_class.h"
#include"db_class.h"

// Operators on 2 IFSs:
// chaos game transform (for volumetric data)
void pure_chaos(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,unsigned int its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: chaos: both IFSs must have the same length>0\n");
		return;
	}
	const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned int its=its_mult*vol2->get_size();
	//vol2->fill((unsigned char)0);
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
	const int ranD=1+RAND_MAX/num_fns;
	unsigned int ix1[3],ix2[3],iy1[3],iy2[3];
	int ran1,ran2;
	double x1[3],y1[3],x2[3],y2[3];
	x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
	x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
	//
	for (unsigned int it=0;it<its;it+=2) {
		ran1=rand()/ranD;
		ran2=rand()/ranD;
		ifs1.apply_fn(ran1,x1,y1);
		ifs2.apply_fn(ran1,x2,y2);
		ifs1.apply_fn(ran2,y1,x1);
		ifs2.apply_fn(ran2,y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
	}
	 /*
	int ran[8];
	for (unsigned int it=0;it<its;it+=8) {
		ran[0]=rand()/ranD;
		ran[1]=rand()/ranD;
		ran[2]=rand()/ranD;
		ran[3]=rand()/ranD;
		ran[4]=rand()/ranD;
		ran[5]=rand()/ranD;
		ran[6]=rand()/ranD;
		ran[7]=rand()/ranD;
		ifs1.apply_fn(ran[0],x1,y1);
		ifs2.apply_fn(ran[0],x2,y2);
		ifs1.apply_fn(ran[1],y1,x1);
		ifs2.apply_fn(ran[1],y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
		ifs1.apply_fn(ran[2],x1,y1);
		ifs2.apply_fn(ran[2],x2,y2);
		ifs1.apply_fn(ran[3],y1,x1);
		ifs2.apply_fn(ran[3],y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
		ifs1.apply_fn(ran[4],x1,y1);
		ifs2.apply_fn(ran[4],x2,y2);
		ifs1.apply_fn(ran[5],y1,x1);
		ifs2.apply_fn(ran[5],y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
		ifs1.apply_fn(ran[6],x1,y1);
		ifs2.apply_fn(ran[6],x2,y2);
		ifs1.apply_fn(ran[7],y1,x1);
		ifs2.apply_fn(ran[7],y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
	}
	*/
}

// deterministic transform (for a list of points, e.g. mesh coordinates)
void pure_deterministic(trilinearIFS ifs1,vertices* verts1,trilinearIFS ifs2,vertices* verts2,int codelength=20) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: deterministic: both IFSs must have the same length>0\n");
		return;
	}
	if (verts1->get_size()!=verts2->get_size()) {
		printf("ERROR: deterministic: both vertices objects must have the same length\n");
		return;
	}
	const unsigned int num_verts=verts1->get_size();
	const unsigned int cl=codelength;
	double x[3],y[3];
	int code[cl];
	for (unsigned int i=0;i<num_verts;i++) {
		verts1->get_vertex(i,x);
		/*
		for (int k=0;k<cl;k++) {
			code[k]=ifs2.find_domain_and_invert(x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		for (int k=cl-1;k>=0;k--) {
			ifs1.apply_fn(code[k],x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		 */
		// assuming codelength%2==0, no real difference in time.
		for (unsigned int k=0;k<cl;k++) {
			code[k++]=ifs2.find_domain_and_invert(x,y);
			code[k]=ifs2.find_domain_and_invert(y,x);
		}
		for (unsigned int k=cl-1;k<cl;k--) {
			ifs1.apply_fn(code[k--],x,y);
			ifs1.apply_fn(code[k],y,x);
		}
		verts2->set_vertex(i,x);
	}
}






unsigned int db_chaos(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,unsigned int its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: chaos: both IFSs must have the same length>0\n");
		return 0;
	}
	const int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	const unsigned int maxits=its_mult*vol2->get_size();
	int dbl=0;
	unsigned int temp=maxits;
	unsigned int temp2=1;
	while (temp>1) {
		dbl++;
		temp/=8;
		temp2*=8;
	}
	//printf("%d\n",dbl);
	const unsigned int its=temp2;
	deBruijn db(8,dbl);
	unsigned int len=db.get_seq_len();
	//printf("%d,%d,%d\n",len,its,maxits);
	//vol2->fill((unsigned char)0);
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
	for (int it=0;it<dbl;it++) {
		ifs1.apply_fn(num_fns-1,x1,y1);
		ifs2.apply_fn(num_fns-1,x2,y2);
	}
	for (unsigned int it=0;it<its;it+=2) {
		ran1=db.next();
		ran2=db.next();
		ifs1.apply_fn(ran1,x1,y1);
		ifs2.apply_fn(ran1,x2,y2);
		ifs1.apply_fn(ran2,y1,x1);
		ifs2.apply_fn(ran2,y2,x2);
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
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((iy1[2]*hei1+iy1[1])*wid1+iy1[0]),(iy2[2]*hei2+iy2[1])*wid2+iy2[0]);
		vol2->set_dat_from_ind(vol1->get_dat_from_ind((ix1[2]*hei1+ix1[1])*wid1+ix1[0]),(ix2[2]*hei2+ix2[1])*wid2+ix2[0]);
	}
	return len;
}




unsigned int original_chaos(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,unsigned int its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: chaos: both IFSs must have the same length>0\n");
		return 0;
	}
	int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	unsigned int its=its_mult*vol2->get_size();
	vol2->fill((unsigned char)0);
	unsigned int wid1=vol1->get_wid();
	unsigned int hei1=vol1->get_hei();
	unsigned int dep1=vol1->get_dep();
	unsigned int wid2=vol2->get_wid();
	unsigned int hei2=vol2->get_hei();
	unsigned int dep2=vol2->get_dep();
	unsigned int ix1[3],ix2[3];
	int ran;
	double x1[3],y1[3],x2[3],y2[3];
	x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
	x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
	int ranD=1+RAND_MAX/num_fns;
	for (unsigned int it=0;it<its;it++) {
		ran=rand()/ranD;
		ifs1.apply_fn(ran,x1,y1);
		ifs2.apply_fn(ran,x2,y2);
		x1[0]=y1[0];x1[1]=y1[1];x1[2]=y1[2];
		x2[0]=y2[0];x2[1]=y2[1];x2[2]=y2[2];
		ix1[0]=0.5+x1[0]*(wid1-1);
		ix1[1]=0.5+x1[1]*(hei1-1);
		ix1[2]=0.5+x1[2]*(dep1-1);
		ix2[0]=0.5+x2[0]*(wid2-1);
		ix2[1]=0.5+x2[1]*(hei2-1);
		ix2[2]=0.5+x2[2]*(dep2-1);
		vol2->set_dat_from_coord(vol1->get_dat_from_coord(ix1[0],ix1[1],ix1[2]),ix2[0],ix2[1],ix2[2]);
	}
	return its;
}


#define _homeo_3d_h



#endif
