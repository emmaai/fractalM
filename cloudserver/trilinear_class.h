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
#include "volume_class.h"

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
