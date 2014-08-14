#include "affine_class.h"
// Operators on 2 IFSs:
// chaos game transform (for volumetric data)
void chaos(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned int its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: chaos: both IFSs must have the same length>0\n");
		return;
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
}

// deterministic transform (for a list of points, e.g. mesh coordinates)
void deterministic(affineIFS ifs1,vertices* verts1,affineIFS ifs2,vertices* verts2,int codelength=20) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: deterministic: both IFSs must have the same length>0\n");
		return;
	}
	if (verts1->get_size()!=verts2->get_size()) {
		printf("ERROR: deterministic: both vertices objects must have the same length\n");
		return;
	}
	unsigned int num_verts=verts1->get_size();
	double x[3],y[3];
	int code[codelength];
	for (unsigned int i=0;i<num_verts;i++) {
		verts1->get_vertex(i,x);
		for (int k=0;k<codelength;k++) {
			code[k]=ifs2.find_domain_and_invert(x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		for (int k=codelength-1;k>=0;k--) {
			ifs1.apply_fn(code[k],x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		verts2->set_vertex(i,x);
	}
}
