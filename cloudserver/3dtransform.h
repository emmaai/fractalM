#ifndef THREEDTRANSFORM
#define THREEDTRANSFORM
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
 

class affine3d{
private:
	double u[4];
	double v[4];
	double w[4];
public:
    affine3d() {
        for (int i=0;i<4;i++) {
            u[i]=0.0;
            v[i]=0.0;
            w[i]=0.0;
        }
        //initialise as identity
        u[0]=1.0;
        v[1]=1.0;
        w[2]=1.0;
    };
    void set(double* dat) {
	    for (int i=0;i<4;i++) u[i]=dat[i];
	    for (int i=0;i<4;i++) v[i]=dat[4+i];
	    for (int i=0;i<4;i++) w[i]=dat[8+i];
    }
    void set_special_case(double C2,double D2,double D3,double* a,double* b,double* c,double* d) {
	    // This is for setting the affine mapping for points of a tetraedron placed in the unit cube as described in the code.
	    u[3]=a[0];
	    u[0]=b[0]-a[0];
	    u[1]=(c[0]-0.5*(a[0]+b[0]))/C2;
	    u[2]=(d[0]-0.5*(a[0]+b[0])-D2*u[1])/D3;
	    v[3]=a[1];
	    v[0]=b[1]-a[1];
	    v[1]=(c[1]-0.5*(a[1]+b[1]))/C2;
	    v[2]=(d[1]-0.5*(a[1]+b[1])-D2*v[1])/D3;
	    w[3]=a[2];
	    w[0]=b[2]-a[2];
	    w[1]=(c[2]-0.5*(a[2]+b[2]))/C2;
	    w[2]=(d[2]-0.5*(a[2]+b[2])-D2*w[1])/D3;
    }
    void set_as_inverse_of(affine3d f) {
	    double A,B,C,D,E,F,G,H,I;
	    A=f.v[1]*f.w[2]-f.v[2]*f.w[1];
	    B=-f.v[0]*f.w[2]+f.v[2]*f.w[0];
	    C=f.v[0]*f.w[1]-f.v[1]*f.w[0];
	    D=-f.u[1]*f.w[2]+f.u[2]*f.w[1];
	    E=f.u[0]*f.w[2]-f.u[2]*f.w[0];
	    F=-f.u[0]*f.w[1]+f.u[1]*f.w[0];
	    G=f.u[1]*f.v[2]-f.u[2]*f.v[1];
	    H=-f.u[0]*f.v[2]+f.u[2]*f.v[0];
	    I=f.u[0]*f.v[1]-f.u[1]*f.v[0];
	    double det=f.u[0]*A+f.u[1]*B+f.u[2]*C;
	    if (fabs(det)<1.0e-6) printf("warning, det close to zeros, %e\n",det);
	    double idet=1.0/(det);
	    u[0]=idet*A;
	    u[1]=idet*D;
	    u[2]=idet*G;
	    v[0]=idet*B;
	    v[1]=idet*E;
	    v[2]=idet*H;
	    w[0]=idet*C;
	    w[1]=idet*F;
	    w[2]=idet*I;
	    u[3]=-(u[0]*f.u[3]+u[1]*f.v[3]+u[2]*f.w[3]);
	    v[3]=-(v[0]*f.u[3]+v[1]*f.v[3]+v[2]*f.w[3]);
	    w[3]=-(w[0]*f.u[3]+w[1]*f.v[3]+w[2]*f.w[3]);
    }
    //void set_as_composition_of(affine3d lf, affine3d rf) {}
    //double* get_fixed_point() {}
    //double* get_eigenvlues() {}
    void apply(double* x,double* y) {
	    y[0]=u[0]*x[0]+u[1]*x[1]+u[2]*x[2]+u[3];
	    y[1]=v[0]*x[0]+v[1]*x[1]+v[2]*x[2]+v[3];
	    y[2]=w[0]*x[0]+w[1]*x[1]+w[2]*x[2]+w[3];
    }
};

bool point_triangle_test(double *,double* ,double* ,double* );
void deterministicTransform(float* , float* , int ,double ,double , double , double );

#endif //THREEDTRANSFORM
