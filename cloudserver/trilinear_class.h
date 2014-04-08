//
//  trilinear_class.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _trilinear_class_h
#define _trilinear_class_h

#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstdio>

const double TOLERANCE=1.0e-6;

// class for a volumetric data slab
class volume{
private:
	unsigned int dim[3];
public:
	unsigned char* slab;
	volume(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=wid;
		dim[1]=hei;
		dim[0]=dep;
		slab=new unsigned char[wid*hei*dep];
		for (unsigned int i=0;i<wid*hei*dep;i++) slab[i]=0;
	}
	~volume(){
		if (dim[0]*dim[1]*dim[2]>0) delete [] slab;
	}
	unsigned int get_size(){
		return dim[0]*dim[1]*dim[2];
	};
	unsigned int get_wid() {
		return dim[2];
	}
	unsigned int get_hei() {
		return dim[1];
	}
	unsigned int get_dep() {
		return dim[0];
	}
	void fill(unsigned char value) {
		for (unsigned int i=0;i<dim[0]*dim[1]*dim[2];i++) slab[i]=value;
	}
	unsigned char get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		return slab[(k*dim[1]+j)*dim[2]+i];
	}
	unsigned char get_dat_from_ind(unsigned int ind) {
		return slab[ind];
	}
	void set_dat_from_coord(unsigned char value, unsigned int i,unsigned int j, unsigned int k) {
		slab[(k*dim[1]+j)*dim[2]+i]=value;
	}
	void set_dat_from_ind(unsigned char value,unsigned int ind) {
		slab[ind]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		if (slab[(k*dim[1]+j)*dim[2]+i]<255) slab[(k*dim[1]+j)*dim[2]+i]++;
	}
	void increment_ind(unsigned int ind) {
		if (slab[ind]<255) slab[ind]++;
	}
	unsigned int sum() {
		unsigned int s=0;
		for (unsigned int i=0;i<dim[0]*dim[1]*dim[2];i++) s+=slab[i];
		return s;
	}
	unsigned int num_more_than(unsigned char a) {
		unsigned int s=0;
		for (unsigned int i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]>a) s++;
		return s;
	}
	unsigned int num_non_zero() {
		return num_more_than(0);
	}
	unsigned int num_less_than(unsigned char a) {
		unsigned int s=0;
		for (unsigned int i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]<a) s++;
		return s;
	}
	void add_sphere(double rad,double* cen,unsigned char value=255) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		unsigned int m,n;
		for (unsigned int k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			m=k*dim[1];
			for (unsigned int j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=(m+j)*dim[2];
				for (unsigned int i=0;i<dim[2];i++) {
					x=1.0*i/(dim[2]-1);
					x2=(x-cen[0])*(x-cen[0]);
					if (x2+y2+z2<=rad2) slab[n+i]=value;
				}
			}
		}
	}
	void save(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		// first byte is the header length
		unsigned char header=13;
		fwrite(&header,sizeof(unsigned char),1,fp);
		// next 12 bytes is the dimensions
		unsigned int dim32[3];
		dim32[0]=(unsigned int) dim[0];
		dim32[1]=(unsigned int) dim[1];
		dim32[2]=(unsigned int) dim[2];
		fwrite(dim32,sizeof(unsigned int),3,fp);
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fwrite(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned char* ptr=slab;
		for (unsigned int i=0;i<dim32[0];i++) {
			fwrite(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
			ptr+=dim32[1]*dim32[2];
		}
		fclose(fp);
	}
	void load(char* filename) {
		FILE* fp;
		fp=fopen(filename,"rb");
		// first byte is the header length
		unsigned char header;
		fread(&header,sizeof(unsigned char),1,fp);
		// first 12 bytes is the dimensions
		unsigned int dim32[3];
		fread(dim32,sizeof(unsigned int),3,fp);
		dim[0]=(unsigned int) dim32[0];
		dim[1]=(unsigned int) dim32[1];
		dim[2]=(unsigned int) dim32[2];
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fread(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned char* ptr=slab;
		for (unsigned int i=0;i<dim32[0];i++) {
			fread(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
			ptr+=dim32[1]*dim32[2];
		}
		fclose(fp);
	}
};

// class for a vertex array
class vertices{
private:
	unsigned int num_vertices;
	double* verts;
public:
	vertices(unsigned int len) {
		num_vertices=len;
		verts=new double[3*num_vertices];
		for (unsigned int i=0;i<3*num_vertices;i++) verts[i]=0.0;
	}
	~vertices(){
		if (num_vertices>0) delete verts;
	}
	unsigned int get_size(){
		return num_vertices;
	};
	double* get_vertex_ptr(unsigned int ind) {
		return &verts[3*ind];
	}
	void get_vertex(unsigned int ind,double* vertex) {
		for (unsigned int i=0;i<3;i++) vertex[i]=verts[3*ind+i];
	}
	void set_vertex(unsigned int ind,double* vertex) {
		for (unsigned int i=0;i<3;i++) verts[3*ind+i]=vertex[i];
	}
	void fill_rand() {
		//fills array with random points, useful for testing
		for (unsigned int i=0;i<3*num_vertices;i++) {
			verts[i]=1.0*rand()/RAND_MAX;
		}
	}
	/*
	// should add routine for saving/loading as a binary stl file
	// this would assume that the vertices are a list of triangles
	// in particular, num_vertices should be a multiple of 3
	// we also need to calculate normals
	void save_stl(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		//..........
		fclose(fp);
	}
	void load_stl(char* filename) {
		FILE* fp;
		fp=fopen(filename,"rb");
		//..........
		fclose(fp);
	}
	*/
};

class trilinear{
private:
	double a[8];
	double b[8];
	double c[8];
public:
	trilinear() {
		//initialise as identity
		for (int i=0;i<8;i++) {
			a[i]=0.0;
			b[i]=0.0;
			c[i]=0.0;
		}
		a[1]=1.0;b[2]=1.0;c[3]=1.0;
	}
	trilinear(const trilinear &fn) {
		//copy constructor
		for (int i=0;i<8;i++) {
			a[i]=fn.a[i];
			b[i]=fn.b[i];
			c[i]=fn.c[i];
		}
	}
	trilinear operator=(const trilinear &fn) {
		for (int i=0;i<8;i++) {
			a[i]=fn.a[i];
			b[i]=fn.b[i];
			c[i]=fn.c[i];
		}
		return *this;
	}
	void set_from_8pts(double* lll,double* rll,double* lrl,double* rrl,double* llr,double* rlr,double* lrr,double* rrr) {
		a[0]=lll[0];b[0]=lll[1];c[0]=lll[2];
		a[1]=rll[0]-a[0];b[1]=rll[1]-b[0];c[1]=rll[2]-c[0];
		a[2]=lrl[0]-a[0];b[2]=lrl[1]-b[0];c[2]=lrl[2]-c[0];
		a[3]=llr[0]-a[0];b[3]=llr[1]-b[0];c[3]=llr[2]-c[0];
		a[4]=rrl[0]-a[0]-a[1]-a[2];b[4]=rrl[1]-b[0]-b[1]-b[2];c[4]=rrl[2]-c[0]-c[1]-c[2];
		a[5]=rlr[0]-a[0]-a[1]-a[3];b[5]=rlr[1]-b[0]-b[1]-b[3];c[5]=rlr[2]-c[0]-c[1]-c[3];
		a[6]=lrr[0]-a[0]-a[2]-a[3];b[6]=lrr[1]-b[0]-b[2]-b[3];c[6]=lrr[2]-c[0]-c[2]-c[3];
		a[7]=rrr[0]-a[0]-a[1]-a[2]-a[3]-a[4]-a[5]-a[6];
		b[7]=rrr[1]-b[0]-b[1]-b[2]-b[3]-b[4]-b[5]-b[6];
		c[7]=rrr[2]-c[0]-c[1]-c[2]-c[3]-c[4]-c[5]-c[6];
	}
	void apply(double* x,double* y) {
		//y=f(x)
		y[0]=a[0]+(a[1]+(a[4]+a[7]*x[2])*x[1]+a[5]*x[2])*x[0]+(a[2]+a[6]*x[2])*x[1]+a[3]*x[2];
		y[1]=b[0]+(b[1]+(b[4]+b[7]*x[2])*x[1]+b[5]*x[2])*x[0]+(b[2]+b[6]*x[2])*x[1]+b[3]*x[2];
		y[2]=c[0]+(c[1]+(c[4]+c[7]*x[2])*x[1]+c[5]*x[2])*x[0]+(c[2]+c[6]*x[2])*x[1]+c[3]*x[2];
	}
	double apply_inverse(double* x, double* y,double eps=TOLERANCE,int maxits=100,int verbose=1){
		// find inverse via newtons method, y=f^{-1}(x)
		// note, there are many inverses and if the initial guess is poor
		//       we will get the wrong one.
		double x0[3],fx[3];
		y[0]=0.5;y[1]=0.5;y[2]=0.5;
		double det,idet,iJ[9],J[9];
		double epsilon=1.0;
		int its=0;
		const double eps2=eps*eps;
		while (epsilon>eps2) {
			x0[0]=y[0];x0[1]=y[1];x0[2]=y[2];
			J[0]=a[1]+(a[4]+a[7]*x0[2])*x0[1]+a[5]*x0[2];
			J[1]=a[2]+(a[4]+a[7]*x0[2])*x0[0]+a[6]*x0[2];
			J[2]=a[3]+(a[5]+a[7]*x0[1])*x0[0]+a[6]*x0[1];
			J[3]=b[1]+(b[4]+b[7]*x0[2])*x0[1]+b[5]*x0[2];
			J[4]=b[2]+(b[4]+b[7]*x0[2])*x0[0]+b[6]*x0[2];
			J[5]=b[3]+(b[5]+b[7]*x0[1])*x0[0]+b[6]*x0[1];
			J[6]=c[1]+(c[4]+c[7]*x0[2])*x0[1]+c[5]*x0[2];
			J[7]=c[2]+(c[4]+c[7]*x0[2])*x0[0]+c[6]*x0[2];
			J[8]=c[3]+(c[5]+c[7]*x0[1])*x0[0]+c[6]*x0[1];
			iJ[0]=J[4]*J[8]-J[5]*J[7];
			iJ[1]=J[2]*J[7]-J[1]*J[8];
			iJ[2]=J[1]*J[5]-J[2]*J[4];
			iJ[3]=J[5]*J[6]-J[3]*J[8];
			iJ[4]=J[0]*J[8]-J[2]*J[6];
			iJ[5]=J[2]*J[3]-J[0]*J[5];
			iJ[6]=J[3]*J[7]-J[4]*J[6];
			iJ[7]=J[1]*J[6]-J[0]*J[7];
			iJ[8]=J[0]*J[4]-J[1]*J[3];
			det=J[0]*iJ[0]+J[1]*iJ[3]+J[2]*iJ[6];
			idet=1.0/det;
			apply(x0,fx);
			fx[0]-=x[0];fx[1]-=x[1];fx[2]-=x[2];
			y[0]=x0[0]-idet*(iJ[0]*fx[0]+iJ[1]*fx[1]+iJ[2]*fx[2]);
			y[1]=x0[1]-idet*(iJ[3]*fx[0]+iJ[4]*fx[1]+iJ[5]*fx[2]);
			y[2]=x0[2]-idet*(iJ[6]*fx[0]+iJ[7]*fx[1]+iJ[8]*fx[2]);
			epsilon=(y[0]-x0[0])*(y[0]-x0[0])+(y[1]-x0[1])*(y[1]-x0[1])+(y[2]-x0[2])*(y[2]-x0[2]);
			its++;
			if (its>maxits) {
				if (verbose>0) printf("WARNING: trilinear->apply_inverse: Newton's method did not converge within %f in %d iterations (current %f)\n",eps,maxits,epsilon);
				break;
			}
		}
		return epsilon;
	}
	bool domain_test(double* x){
		// A general domain test is complicated and costly
		// it is much better if one is able to exploit the IFS structure
		// Two approaches: 1) check the 6*2 planes
		//                 2) see if inverse is in unit square
		double y[3];
		double eps=apply_inverse(x,y);
		if (eps<TOLERANCE && y[0]>=0.0 && y[0]<=1.0 && y[1]>=0.0 && y[1]<=1.0 && y[2]>=0.0 && y[2]<=1.0) {
			return true;
		} else {
			return false;
		}
	}
	// should probably add a convexity test.
};

class trilinearIFS{
private:
	int num_fns;
	trilinear* fns;
public:
	//constructors
	trilinearIFS() {
		num_fns=0;
	}
	trilinearIFS(int n) {
		num_fns=n;
		fns=new trilinear[n];
	}
	trilinearIFS(const trilinearIFS &ifs) {
		num_fns=ifs.num_fns;
		fns=new trilinear[num_fns];
		for (int i=0;i<num_fns;i++) fns[i]=ifs.fns[i];
	}
	trilinearIFS operator=(const trilinearIFS &ifs) {
		num_fns=ifs.num_fns;
		fns=new trilinear[num_fns];
		for (int i=0;i<num_fns;i++) fns[i]=ifs.fns[i];
		return *this;
	}
	~trilinearIFS() {
		if (num_fns>0) delete[] fns;
	}
	void set_len(int n) {
		if (num_fns>0) delete fns;
		num_fns=n;
		fns=new trilinear[n];
	}
	void set_fn(int index,trilinear fn) {
		fns[index]=fn;
	}
	trilinear get_fn(int index) {
		return fns[index];
	}
	int len() {
		return num_fns;
	}
	void apply_fn(int index,double* x, double* y) {
		fns[index].apply(x,y);
	}
	void apply_inverse_fn(int index,double* x, double* y) {
		fns[index].apply_inverse(x,y);
	}
	int find_domain(double* x){
		for (int i=0;i<num_fns;i++) {
			if (fns[i].domain_test(x)) return i;
		}
		printf("ERROR: trilinearIFS->find_domain: no domain tests were successful\n");
	}
	int find_domain_and_invert(double* x,double*y) {
		int index=-1;
		double eps;
		for (int i=0;i<num_fns;i++) {
			eps=fns[i].apply_inverse(x,y,TOLERANCE,100,0);
			if (eps<TOLERANCE && y[0]>=0.0 && y[0]<=1.0 && y[1]>=0.0 && y[1]<=1.0 && y[2]>=0.0 && y[2]<=1.0) {
				index=i;
				break;
			}
		}
		if (index==-1) printf("ERROR: trilinearIFS->find_domain_and_invert: no domain tests were successful\n");
		return index;
	}
	void density_plot(volume *vol,unsigned int its_mult=4) {
		//perform a density plot on a volumetric slab
		//for now this will be just a brief test
		unsigned int its=its_mult*vol->get_size();
		vol->fill((unsigned char)0);
		int wid=vol->get_wid();
		int hei=vol->get_hei();
		int dep=vol->get_dep();
		int ix[3];
		int ran;
		double x[3],y[3];
		x[0]=0.5;
		x[1]=0.5;
		x[2]=0.5;
		int ranD=1+RAND_MAX/num_fns;
		for (unsigned int it=0;it<its;it++) {
			ran=rand()/ranD;
			apply_fn(ran,x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
			ix[0]=0.5+x[0]*(wid-1);
			ix[1]=0.5+x[1]*(hei-1);
			ix[2]=0.5+x[2]*(dep-1);
			vol->increment_coord(ix[0],ix[1],ix[2]);
		}
	}
};

void chaos(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,unsigned int its_mult);

void deterministic(trilinearIFS ifs1,vertices* verts1,trilinearIFS ifs2,vertices* verts2,int codelength);

#endif
