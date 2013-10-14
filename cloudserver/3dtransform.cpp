#include "3dtransform.h"
int CASE=1;
bool DATA_OUTPUT=true;

 
/*
 This tests if the point P is on the side of the triangle 
	as given by the RH rule. 
	(vectors B-A and C-A for index and middle fingers respectively)
 */
bool point_triangle_test(double* P,double* A,double* B,double* C)
{
	double N[3];
	N[0]=(B[1]-A[1])*(C[2]-A[2])-(B[2]-A[2])*(C[1]-A[1]);
	N[1]=-(B[0]-A[0])*(C[2]-A[2])+(B[2]-A[2])*(C[0]-A[0]);
	N[2]=(B[0]-A[0])*(C[1]-A[1])-(B[1]-A[1])*(C[0]-A[0]);
	// Normalising N is not really necessary
	/*
	 // This finds the point Q in the plane which is closest to P
	double M11=pow(B[0]-A[0],2.0)+pow(B[1]-A[1],2.0)+pow(B[2]-A[2],2.0);
	double M12=(B[0]-A[0])*(C[0]-A[0])+(B[1]-A[1])*(C[1]-A[1])+(B[2]-A[2])*(C[2]-A[2]);
	double M21=M12;
	double M22=pow(C[0]-A[0],2.0)+pow(C[1]-A[1],2.0)+pow(C[2]-A[2],2.0);
	double det=M11*M22-M12*M21;
	if (fabs(det)<1.0e-6) printf("Warning: determinantis small %e\n",det);
	double idet=1.0/det;
	double b1=(B[0]-A[0])*(A[0]-P[0])+(B[1]-A[1])*(A[1]-P[1])+(B[2]-A[2])*(A[2]-P[2]);
	double b2=(A[0]-P[0])*(C[0]-A[0])+(A[1]-P[1])*(C[1]-A[1])+(A[2]-P[2])*(C[2]-A[2]);
	double alpha=-idet*(M22*b1-M12*b2);
	double beta=-idet*(-M21*b1+M11*b2);
	double Q[3];
	for (int i=0;i<3;i++) {
		Q[i]=P[i]-(A[i]+alpha*(B[i]-A[i])+beta*(C[i]-A[i]));
	 }
	 double dot=Q[0]*N[0]+Q[1]*N[1]+Q[2]*N[2];
	 */
	// Alternatively, test N.(P-A)
	double dot=(P[0]-A[0])*N[0]+(P[1]-A[1])*N[1]+(P[2]-A[2])*N[2];
	return (dot>=0.0);
}

void deterministicTransform(float* svertices, float* vertices,
	int count,double xt,double yt, double zt, double pp)
{

    double C2 = 1.0;			//1.0	or sqrt(0.75)
    double D2 = sqrt(3.0)/6.0;	//0.375	or sqrt(3.0)/6.0?
    double D3 = sqrt(2.0/3.0);	//1.0	or sqrt(2.0/3.0)?

    double alpha=pp;
    double beta= pp;
    double gamma=pp;
    double A[3],B[3],C[3],D[3],P1[3],P2[3],P3[3];

    A[0]=0.0;
    A[1]=0.0;
    A[2]=0.0;
    B[0]=1.0;
    B[1]=0.0;
    B[2]=0.0;
    C[0]=0.5;
    C[1]=C2;
    C[2]=0.0;
    D[0]=0.5;
    D[1]=D2;
    D[2]=D3;
    P1[0]=A[0]+alpha*(B[0]-A[0]);
    P1[1]=A[1]+alpha*(B[1]-A[1]);
    P1[2]=A[2]+alpha*(B[2]-A[2]);
    P2[0]=B[0]+beta*(C[0]-B[0]);
    P2[1]=B[1]+beta*(C[1]-B[1]);
    P2[2]=B[2]+beta*(C[2]-B[2]);
    P3[0]=C[0]+gamma*(A[0]-C[0]);
    P3[1]=C[1]+gamma*(A[1]-C[1]);
    P3[2]=C[2]+gamma*(A[2]-C[2]);

    /*
     This is one possible mapping (I'm not sure I like this one)
     Note the rhs's are the a,b,c,d
     f1 maps
     A->D, B->A, C->A+alpha(B-A)=P1, D->C+gamma(A-C)=P3
     f2 maps
     A->D, B->B+beta(C-B)=P2, C->A+alpha(B-A)=P1, D->B
     f3 maps
     A->D, B->B+beta(C-B)=P2, C->C, D->C+gamma(A-C)=P3
     f4 maps
     A->D, B->B+beta(C-B)=P2, C->A+alpha(B-A)=P1, D->C+gamma(A-C)=P3

     An alternative (the one I first wrote down) is
     f1 maps
     A->D, B->A+alpha(B-A)=P1, C->A, D->C+gamma(A-C)=P3
     f2 maps
     A->D, B->A+alpha(B-A)=P1, C->B+beta(C-B)=P2, D->B
     f3 maps
     A->D, B->C, C->B+beta(C-B)=P2, D->C+gamma(A-C)=P3
     f4 maps
     A->D, B->A+alpha(B-A)=P1, C->B+beta(C-B)=P2, D->C+gamma(A-C)=P3

     */

    affine3d f1,f2,f3,f4;

    if (CASE==0) {
        f1.set_special_case(C2,D2,D3,D,A,P1,P3);
        f2.set_special_case(C2,D2,D3,D,P2,P1,B);
        f3.set_special_case(C2,D2,D3,D,P2,C,P3);
        f4.set_special_case(C2,D2,D3,D,P2,P1,P3);
    } else if (CASE==1) {
        f1.set_special_case(C2,D2,D3,D,P1,A,P3);
        f2.set_special_case(C2,D2,D3,D,P1,P2,B);
        f3.set_special_case(C2,D2,D3,D,C,P2,P3);
        f4.set_special_case(C2,D2,D3,D,P1,P2,P3);
    }

    /*
     We need a colour stealing mapset as well: g1,g2,g3,g4
     */

    double alpha2=1.0-pp;
    double beta2= 1.0-pp;
    double gamma2=1.0-pp;
    double Q1[3],Q2[3],Q3[3];

    Q1[0]=A[0]+alpha2*(B[0]-A[0]);
    Q1[1]=A[1]+alpha2*(B[1]-A[1]);
    Q1[2]=A[2]+alpha2*(B[2]-A[2]);
    Q2[0]=B[0]+beta2*(C[0]-B[0]);
    Q2[1]=B[1]+beta2*(C[1]-B[1]);
    Q2[2]=B[2]+beta2*(C[2]-B[2]);
    Q3[0]=C[0]+gamma2*(A[0]-C[0]);
    Q3[1]=C[1]+gamma2*(A[1]-C[1]);
    Q3[2]=C[2]+gamma2*(A[2]-C[2]);

    affine3d g1,g2,g3,g4;

    g1.set_special_case(C2,D2,D3,D,A,Q1,Q3);
    g2.set_special_case(C2,D2,D3,D,Q2,Q1,B);
    g3.set_special_case(C2,D2,D3,D,Q2,C,Q3);
    g4.set_special_case(C2,D2,D3,D,Q2,Q1,Q3);
    if (CASE==0) {
        g1.set_special_case(C2,D2,D3,D,A,Q1,Q3);
        g2.set_special_case(C2,D2,D3,D,Q2,Q1,B);
        g3.set_special_case(C2,D2,D3,D,Q2,C,Q3);
        g4.set_special_case(C2,D2,D3,D,Q2,Q1,Q3);
    } else if (CASE==1) {
        g1.set_special_case(C2,D2,D3,D,Q1,A,Q3);
        g2.set_special_case(C2,D2,D3,D,Q1,Q2,B);
        g3.set_special_case(C2,D2,D3,D,C,Q2,Q3);
        g4.set_special_case(C2,D2,D3,D,Q1,Q2,Q3);
    }

    affine3d ig1,ig2,ig3,ig4;
    ig1.set_as_inverse_of(g1);
    ig2.set_as_inverse_of(g2);
    ig3.set_as_inverse_of(g3);
    ig4.set_as_inverse_of(g4);

    //Now do a deterministic loop over the vertices
    double x[3],y[3],x2[3],y2[3];
    int codelength=20;
    char code[codelength];
    for (int i=0;i<count;i+=3)
    {
        x[0]=svertices[i];
        x[1]=svertices[i+1];
        x[2]=svertices[i+2];
        //Transform x onto y, e.g. here is identity sample
        x2[0]=x[0]+xt;
        x2[1]=x[1]+yt;
        x2[2]=x[2]+zt;
        //We really should test to make sure x2 is in the tetrahedron
        for (int j=0;j<codelength;j++)
	{
            //check which domain we lie in, apply inverse, record code.
            if (point_triangle_test(x2,Q3,Q1,D)) {
                ig1.apply(x2,y2);
                code[j]=0;
            } else if (point_triangle_test(x2,Q1,Q2,D)) {
                ig2.apply(x2,y2);
                code[j]=1;
            } else if (point_triangle_test(x2,Q2,Q3,D)) {
                ig3.apply(x2,y2);
                code[j]=2;
            } else {
                ig4.apply(x2,y2);
                code[j]=3;
            }
            x2[0]=y2[0];
            x2[1]=y2[1];
            x2[2]=y2[2];
        }
        for (int j=codelength-1;j>=0;j--)
	{
            //Now map forwards using same code
            if (code[j]==0) {
                f1.apply(x2,y2);
            } else if (code[j]==1) {
                f2.apply(x2,y2);
            } else if (code[j]==2) {
                f3.apply(x2,y2);
            } else {
                f4.apply(x2,y2);
            }
            x2[0]=y2[0];
            x2[1]=y2[1];
            x2[2]=y2[2];
        }
        y[0]=x2[0]-xt;
        y[1]=x2[1]-yt;
        y[2]=x2[2]-zt;
        //y[0]=x[0]-xt/10;
        //y[1]=x[1]-yt/10;
        //y[2]=x[2]-zt/10;
        //Now copy to vertex array
        vertices[i]=y[0];
        vertices[i+1]=y[1];
        vertices[i+2]=y[2];
    }
}
