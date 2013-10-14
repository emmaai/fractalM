#ifndef TRANSFMIMG
#define TRANSFMIMG
void *transfmImage(void *);
void *transformLHS(void *);
void *transformRHS(void *);
char *applytransform1(unsigned char *, unsigned char *, int, int, int, double *, double *, int);
char *applytransform2(unsigned char *, unsigned char *, int, int, int, double *, double *, int);
char *applytransform3(unsigned char *, unsigned char *, int, int, int, double *, double *, int);
char *applytransform4(unsigned char *, unsigned char *, int, int, int, double *, double *, int);
char *applytransform(unsigned char *, unsigned char *, int, int, int, double *, double *, int);
#endif //TRANSFMIMG
