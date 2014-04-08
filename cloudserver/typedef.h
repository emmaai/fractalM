#ifndef TYPEDEF
#define TYPEDEF
typedef struct {
    float x;
    float y;
    float z;
}nodeCoordinate;
typedef struct {
//parameters 1, 2, 3, 5, 5, 7 are for similitude and affine
//parameters 1, 2, 3, 5, 6, 7, 9, A, B are for projective
//parameters 1, 2, 3, 4, 5, 6, 7, 8 are for bilinear
    float param1;
    float param2;
    float param3;
    float param4;
    float param5;
    float param6;
    float param7;
    float param8;
    float param9;
    float paramA;
    float paramB;
}allParams;

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}pixelRGB;

typedef struct {
    //in pixel
    unsigned long xLength; 
    unsigned long yWidth; 
    unsigned long zHeight;
}imageSize;

typedef struct {
    int funcNo;
    nodeCoordinate coordinate[8];
    imageSize resolution;
}activeFunc;

typedef union{
    unsigned char *image;
    pixelRGB *pixel;
}frameBuffer;

typedef struct{
    int socketID;
    unsigned char *message;
    unsigned long messageSize;
}threadData;

#define PARAMNUMBER 8
#endif //TYPEDEF
