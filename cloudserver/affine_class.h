//
//  affine_class.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _affine_class_h
#define _affine_class_h

#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include "volume_class.h"

class affine{
private:
	double a[4];
	double b[4];
	double c[4];
public:
	affine() {
		//initialise as identity
		for (int i=0;i<4;i++) {
			a[i]=0.0;
			b[i]=0.0;
			c[i]=0.0;
		}
		a[1]=1.0;b[2]=1.0;c[3]=1.0;
	}
	affine(const affine &fn) {
		//copy constructor
		for (int i=0;i<4;i++) {
			a[i]=fn.a[i];
			b[i]=fn.b[i];
			c[i]=fn.c[i];
		}
	}
	affine operator=(const affine &fn) {
		for (int i=0;i<4;i++) {
			a[i]=fn.a[i];
			b[i]=fn.b[i];
			c[i]=fn.c[i];
		}
		return *this;
	}
	void set_special_case(double C2,double D2,double D3,double* A,double* B,double* C,double* D) {
		// This is for setting the affine mapping for points of a tetraedron placed in the unit cube as described below:
		// The 4 domain points are (0,0,0), (1,0,0), (0.5,C2,0.0), (0.5,D2,D3)
		// The 4 target points are A, B, C, D
		a[0]=A[0];
		a[1]=B[0]-A[0];
		a[2]=(C[0]-0.5*(A[0]+B[0]))/C2;
		a[3]=(D[0]-0.5*(A[0]+B[0])-D2*a[2])/D3;
		b[0]=A[1];
		b[1]=B[1]-A[1];
		b[2]=(C[1]-0.5*(A[1]+B[1]))/C2;
		b[3]=(D[1]-0.5*(A[1]+B[1])-D2*b[2])/D3;
		c[0]=A[2];
		c[1]=B[2]-A[2];
		c[2]=(C[2]-0.5*(A[2]+B[2]))/C2;
		c[3]=(D[2]-0.5*(A[2]+B[2])-D2*c[2])/D3;
	}
	void set_from_4pt_mapping(double* dt1,double* dt2,double* dt3,double* dt4,double* rt1,double* rt2,double* rt3,double* rt4) {
		// e.g. the mapping of one tetrahedron to a smaller one
		// (dt1,dt2,dt3,dt4) is the domain tetrahedron
		// (rt1,rt2,rt3,rt4) is the range tetrahedron
		double C[9];
		double idet;
		double tx[3];
		// First, find a[1],a[2],a[3] then a[0]
		C[0]=(dt3[1]-dt1[1])*(dt4[2]-dt1[2])-(dt3[2]-dt1[2])*(dt4[1]-dt1[1]);
		C[1]=(dt2[2]-dt1[2])*(dt4[1]-dt1[1])-(dt2[1]-dt1[1])*(dt4[2]-dt1[2]);
		C[2]=(dt2[1]-dt1[1])*(dt3[2]-dt1[2])-(dt2[2]-dt1[2])*(dt3[1]-dt1[1]);
		C[3]=(dt3[2]-dt1[2])*(dt4[0]-dt1[0])-(dt3[0]-dt1[0])*(dt4[2]-dt1[2]);
		C[4]=(dt2[0]-dt1[0])*(dt4[2]-dt1[2])-(dt2[2]-dt1[2])*(dt4[0]-dt1[0]);
		C[5]=(dt2[2]-dt1[2])*(dt3[0]-dt1[0])-(dt2[0]-dt1[0])*(dt3[2]-dt1[2]);
		C[6]=(dt3[0]-dt1[0])*(dt4[1]-dt1[1])-(dt3[1]-dt1[1])*(dt4[0]-dt1[0]);
		C[7]=(dt2[1]-dt1[1])*(dt4[0]-dt1[0])-(dt2[0]-dt1[0])*(dt4[1]-dt1[1]);
		C[8]=(dt2[0]-dt1[0])*(dt3[1]-dt1[1])-(dt2[1]-dt1[1])*(dt3[0]-dt1[0]);
		idet=1.0/((dt2[0]-dt1[0])*C[0]+(dt2[1]-dt1[1])*C[3]+(dt2[2]-dt1[2])*C[6]);
		tx[0]=rt2[0]-rt1[0];tx[1]=rt3[0]-rt1[0];tx[2]=rt4[0]-rt1[0];
		a[1]=idet*(C[0]*tx[0]+C[1]*tx[1]+C[2]*tx[2]);
		a[2]=idet*(C[3]*tx[0]+C[4]*tx[1]+C[5]*tx[2]);
		a[3]=idet*(C[6]*tx[0]+C[7]*tx[1]+C[8]*tx[2]);
		a[0]=rt1[0]-a[1]*dt1[0]-a[2]*dt1[1]-a[3]*dt1[2];
		// Now for b[1],b[2],b[3] then b[0]
		tx[0]=rt2[1]-rt1[1];tx[1]=rt3[1]-rt1[1];tx[2]=rt4[1]-rt1[1];
		b[1]=idet*(C[0]*tx[0]+C[1]*tx[1]+C[2]*tx[2]);
		b[2]=idet*(C[3]*tx[0]+C[4]*tx[1]+C[5]*tx[2]);
		b[3]=idet*(C[6]*tx[0]+C[7]*tx[1]+C[8]*tx[2]);
		b[0]=rt1[1]-b[1]*dt1[0]-b[2]*dt1[1]-b[3]*dt1[2];
		// Now for c[1],c[2],c[3] then c[0]
		tx[0]=rt2[2]-rt1[2];tx[1]=rt3[2]-rt1[2];tx[2]=rt4[2]-rt1[2];
		c[1]=idet*(C[0]*tx[0]+C[1]*tx[1]+C[2]*tx[2]);
		c[2]=idet*(C[3]*tx[0]+C[4]*tx[1]+C[5]*tx[2]);
		c[3]=idet*(C[6]*tx[0]+C[7]*tx[1]+C[8]*tx[2]);
		c[0]=rt1[2]-c[1]*dt1[0]-c[2]*dt1[1]-c[3]*dt1[2];
		
	}
	void apply(double* x,double* y) {
		//y=f(x)
		y[0]=a[0]+a[1]*x[0]+a[2]*x[1]+a[3]*x[2];
		y[1]=b[0]+b[1]*x[0]+b[2]*x[1]+b[3]*x[2];
		y[2]=c[0]+c[1]*x[0]+c[2]*x[1]+c[3]*x[2];
	}
	void apply_inverse(double* x, double* y){
		// make co-factor matrix (transpose)
		double C[9];
		C[0]=b[2]*c[3]-b[3]*c[2];
		C[1]=a[3]*c[2]-a[2]*c[3];
		C[2]=a[2]*b[3]-a[3]*b[2];
		C[3]=b[3]*c[1]-b[1]*c[3];
		C[4]=a[1]*c[3]-a[3]*c[1];
		C[5]=a[3]*b[1]-a[1]*b[3];
		C[6]=b[1]*c[2]-b[2]*c[1];
		C[7]=a[2]*c[1]-a[1]*c[2];
		C[8]=a[1]*b[2]-a[2]*c[1];
		double idet=1.0/(a[1]*C[0]+a[2]*C[3]+a[3]*C[6]);
		double tx[3]={x[0]-a[0],x[1]-b[0],x[2]-c[0]};
		y[0]=idet*(C[0]*tx[0]+C[1]*tx[1]+C[2]*tx[2]);
		y[1]=idet*(C[3]*tx[0]+C[4]*tx[1]+C[5]*tx[2]);
		y[2]=idet*(C[6]*tx[0]+C[7]*tx[1]+C[8]*tx[2]);
	}
	bool domain_test(double* x){
		// NOTE: implement for a dterministic method
		return false;
	}
};

class affineIFS{
private:
	int num_fns;
	affine* fns;
public:
	//constructors
	affineIFS() {
		num_fns=0;
	}
	affineIFS(int n) {
		num_fns=n;
		fns=new affine[n];
	}
	affineIFS(const affineIFS &ifs) {
		num_fns=ifs.num_fns;
		fns=new affine[num_fns];
		for (int i=0;i<num_fns;i++) fns[i]=ifs.fns[i];
	}
	affineIFS operator=(const affineIFS &ifs) {
		num_fns=ifs.num_fns;
		fns=new affine[num_fns];
		for (int i=0;i<num_fns;i++) fns[i]=ifs.fns[i];
		return *this;
	}
	~affineIFS() {
		if (num_fns>0) delete[] fns;
	}
	void set_len(int n) {
		if (num_fns>0) delete fns;
		num_fns=n;
		fns=new affine[n];
	}
	void set_fn(int index,affine fn) {
		fns[index]=fn;
	}
	affine get_fn(int index) {
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
		return -1;
	}
	int find_domain_and_invert(double* x,double*y) {
		// NOTE: need to implement for a deterministic method
		return -1;
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


void chaos(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned int its_mult);
void deterministic(affineIFS ifs1,vertices* verts1,affineIFS ifs2,vertices* verts2,int codelength);

#endif
