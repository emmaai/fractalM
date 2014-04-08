/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "rwsockthread.h"
#include "transfmimg.h"
#include "typedef.h"
#include "trilinear_class.h"
#include "db_class.h"
#include "ddsbase.h"

using namespace std;

pthread_mutex_t mutex;
extern volatile bool sockClose;
extern volatile unsigned long imageTargetSize;
extern volatile bool imageTargetReady;
extern volatile bool displayHR;
unsigned char *imageBufferTarget;
extern unsigned char *imageBufferSource;
volume *vol1, *vol2, *vol3, *vol4;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

 
bool getNextLine(ifstream *file_, string& type, string& args, bool toLowercase) {
    string whitespace_ = " \t\n\r";
    string commentChars_ = "#";
    string separators_ = " \t\n\r";
    if (file_->eof())
        return false;

    do {
        string line;
        getline(*file_, line);

        size_t type_start = line.find_first_not_of(whitespace_);
        if (!line.empty() && type_start != string::npos && (commentChars_.find(line[type_start]) == string::npos)) {
            size_t sep_start = line.find_first_of(separators_, type_start);
            size_t type_size = string::npos;
            if (sep_start != string::npos) {
                type_size = sep_start - type_start;
                size_t args_start = line.find_first_not_of(separators_, sep_start);
                if (args_start != string::npos) {
                    // skip trailing whitespace
                    size_t args_end = line.find_last_not_of(whitespace_);
                    args = line.substr(args_start,
                                       (args_end != string::npos ? args_end - args_start + 1 : string::npos));
                }
                else
                    args = "";

            }
            type = line.substr(type_start, type_size);
            if (toLowercase)
                transform(type.begin(), type.end(), type.begin(), (int (*)(int))tolower);

            return true;
        }
    } while (!file_->eof());

    return false;
}

bool getNextLine(ifstream *file_, string &type, istringstream &args, bool toLowercase)
{    
    string s;
    bool r = getNextLine(file_, type, s, toLowercase);
    args.clear();
    args.rdbuf()->str(s);
    return r;
}

void transfmVolume(ifstream *filel, ifstream *filer, volume *srcvolume, volume *tgtvolume)
{
    int i, j, iter;
    double p[8][3];
    trilinear fn;
    trilinearIFS ifs1(8), ifs2(8);
    string type;
    istringstream args;
    
    for(i=0; i<8; i++)
    {
	if(getNextLine(filel, type, args, false))
	    for(j=0; j<8; j++)	
	    {
		args >> p[j][0];   
		args >> p[j][1];   
		args >> p[j][2];   
		printf("coordinate is %f %f %f\n", p[j][0], p[j][1], p[j][2]);
	    }
	    fn.set_from_8pts(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
	    ifs1.set_fn(i, fn);
    }

    for(i=0; i<8; i++)
    {
	if(getNextLine(filer, type, args, false))
	    for(j=0; j<8; j++)	
	    {
		args >> p[j][0];   
		args >> p[j][1];   
		args >> p[j][2];   
		printf("coordinate is %f %f %f\n", p[j][0], p[j][1], p[j][2]);
	    }
	    fn.set_from_8pts(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
	    ifs2.set_fn(i, fn);
    }
	iter = db_chaos_parallel(ifs1,srcvolume,ifs2,tgtvolume,4);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid, rs, buffersize, n;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     pthread_t thread_rw, thread_cpt;
     threadData threadArg;

     if (argc < 5) {
         fprintf(stderr,"ERROR, server inputrawfile outputrawfile param1 param2 [clip]\n");
         exit(1);
     }
     /*
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     */

    buffersize = 32768*8;
    pthread_mutex_init(&mutex, NULL);
    unsigned int widthLR, heightLR, depthLR, widthHR, heightHR, depthHR, size;
    string type;
    istringstream args;
    string rawfnHR, rawfnLR;

    ifstream *datfn = new ifstream(argv[1]);
    if(!datfn->is_open())
    {
	printf("can't open dat file \n"); 
	return 1;
    }

    while(getNextLine(datfn, type, args, false))
    {
	if (type == "ObjectFileName:") {
	    args >> rawfnHR;   
	    printf("raw file name is %s\n", rawfnHR.c_str());
	 }else if (type == "Resolution:") 
	 {
            args >> widthHR;
            args >> heightHR;
            args >> depthHR;
	    printf("high resolution is %d %d %d\n", widthHR, heightHR, depthHR);
	 }

    }
    datfn->close();
    delete(datfn);

    
/*
    vol1 = new volume(2*1024, 3*1024, 1024);
    vol2 = new volume(2*1024, 3*1024, 1024);

    vol3 = new volume(1024, 1024, 1024);
    vol4 = new volume(1024, 1024, 1024);

*/
/*
    vol1 = new volume(widthLR, heightLR, depthLR);
    vol2 = new volume(widthLR, heightLR, depthLR);
    */

    vol3 = new volume(widthHR, heightHR, depthHR);
    vol4 = new volume(widthHR, heightHR, depthHR);

/*
    imageBufferTarget = new unsigned char[widthHR*heightHR*depthHR];
    if(!imageBufferTarget)
    {
	printf("new buffer failed\n");
    }
    printf("image buffer pointer is %ul\n", imageBufferTarget);
    printf("vol2 pointer is %ul\n", vol2);
    */

    unsigned char *data = readRAWfile((char *)rawfnHR.c_str(), &size);
    printf("data pointer is %ul\n", (unsigned long)data);
    for(int i=0; i<widthHR*heightHR*depthHR; i++ )
	vol3->set_dat_from_ind(data[i], i);
    delete data;

/* read in parameters */
    ifstream *paramfnl = new ifstream(argv[3]);
    if(!paramfnl->is_open())
    {
	printf("can't open parameter file \n"); 
	return 1;
    }

    ifstream *paramfnr = new ifstream(argv[4]);
    if(!paramfnr->is_open())
    {
	printf("can't open parameter file \n"); 
	return 1;
    }

    transfmVolume(paramfnl, paramfnr, vol3, vol4);

    char *filename = argv[2];

    if(argv[5])
    {
	float rightVal, leftVal, frontVal, backVal, bottomVal, topVal; 
	unsigned long dimx, dimy, dimz, ind;
	datfn = new ifstream(argv[5]);
	if(!datfn->is_open())
	{
	    printf("can't open dat file \n"); 
	    return 1;
	}
	while(getNextLine(datfn, type, args, false))
	{
	    if (type == "clipRight:") {
		args >> rightVal;   
	     }else if (type == "clipLeft:") 
	     {
		args >> leftVal;
	     }else if (type == "clipFront:") 
	     {
		args >> frontVal; 
	     }else if (type == "clipBack:") 
	     {
		args >> backVal;
	     }else if (type == "clipBottom:") 
	     {
		args >> bottomVal;
	     }else if (type == "clipTop:") 
	     {
		args >> topVal;
	    }
	}

	printf("clipping plane is %f %f %f %f %f %f\n", rightVal, leftVal, frontVal, backVal, bottomVal, topVal);

	datfn->close();
	delete(datfn);
	dimx  = (unsigned long)(leftVal + 1.0f-rightVal);
	dimy  = (unsigned long)(backVal + 1.0f-frontVal);
	dimz  = (unsigned long)(topVal + 1.0f-bottomVal);

	printf("new dimension is %d %d %d\n", dimx, dimy, dimz);
	data = new unsigned char[dimx*dimy*dimz];
	for(int k=0; k<dimz; k++)
	    for(int j=0; j<dimy; j++)
	    {
		ind = ((k+(unsigned long)bottomVal)*heightHR+(j+(unsigned long)frontVal))*widthHR+(unsigned long)rightVal;
		memcpy(&data[(k*dimy+j)*dimx], &vol4->slab[ind], dimx);
	    }

	writeRAWfile(filename, data, dimx*dimy*dimz, 1);
	delete[] data;

    }else
    {
	writeRAWfile(filename,vol4->slab, vol4->get_size(), 1);
    }

    delete vol3;
    delete vol4;

/*
    data = readRAWfile((char *)rawfnLR.c_str(), &size);
    for(int i=0; i<widthLR*heightLR*depthLR; i++ )
	vol1->set_dat_from_ind(data[i], i);
    delete data;

*/
/*
     while(1)
     {
	 newsockfd = accept(sockfd, 
		(struct sockaddr *) &cli_addr, &clilen);
	printf("open a new socket %d\n", newsockfd);
	 if (newsockfd < 0) 
	     error("ERROR on accept");
	 threadArg.socketID = newsockfd;
	 threadArg.message = new unsigned char[buffersize];
	 threadArg.messageSize = buffersize;
	 rs = pthread_create(&thread_rw, NULL, rSocket, (void *)&threadArg);
	 if(rs)
	 {
		error("ERROR on creating thread_rw");
	 }
	 printf("create another thread \n");
	 pthread_mutex_lock(&mutex);
	 sockClose = false;
	 pthread_mutex_unlock(&mutex);
	 rs = pthread_create(&thread_cpt, NULL, transfmImage, (void *)&threadArg);

	 if(rs)
	 {
		error("ERROR on creating thread_cpt");
	 }

	while(1)
	{
	    if(imageTargetReady)
	    {
		if(displayHR)
		{
		    pthread_mutex_lock(&mutex);
		    displayHR = false;
		    pthread_mutex_unlock(&mutex);
		    size = widthHR*heightHR*depthHR;
		}else
		    size = widthLR*heightLR*depthLR;
		printf("volume size is %d, %d, %d\n", widthLR, heightLR, depthLR);

		printf("write image to client %d\n", size);
		n = write(newsockfd, "<DATA", 5);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket %d\n", errno);
		    break;
		}
		n = write(newsockfd,imageBufferTarget,size);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket %d\n", errno);
		    break;
		}
		n = write(newsockfd, "<\\DATA", 6);
		printf("actual write %d\n", n);
		if (n < 0) 
	       {
		    printf("ERROR writing to socket %d\n", errno);
		    break;
		}
		pthread_mutex_lock(&mutex);
		imageTargetReady = false;
		pthread_mutex_unlock(&mutex);
	    }
	    if(sockClose)
		break;
	
	}
	printf("write while is break\n");
	 pthread_join(thread_rw, NULL);
	 printf("closed by the client, thread_rw ending\n");
	 close(newsockfd);
	 pthread_join(thread_cpt, NULL);

    }//end of while
    close(sockfd);
     printf("close the server socket\n");
     pthread_exit(NULL);
    delete[] imageBufferTarget;
    */

    return 0; /* we never get here */
}
