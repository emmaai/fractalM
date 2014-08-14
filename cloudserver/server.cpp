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


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid, rs, buffersize, n;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     pthread_t thread_rw, thread_cpt;
     threadData threadArg;

     if (argc < 4) {
         fprintf(stderr,"ERROR, server portno filename filename\n");
         exit(1);
     }
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

    buffersize = 32768*8;
    pthread_mutex_init(&mutex, NULL);
    unsigned int widthLR, heightLR, depthLR, widthHR, heightHR, depthHR, size;
    string type;
    istringstream args;
    string rawfnHR, rawfnLR;
    char *filename = argv[2];

    ifstream *datfn = new std::ifstream(argv[2]);
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

    datfn = new std::ifstream(argv[3]);
    if(!datfn->is_open())
    {
	printf("can't open dat file \n"); 
	return 1;
    }

    while(getNextLine(datfn, type, args, false))
    {
	if (type == "ObjectFileName:") {
	    args >> rawfnLR;   
	    printf("raw file name is %s\n", rawfnLR.c_str());
	 }else if (type == "Resolution:") 
	 {
            args >> widthLR;
            args >> heightLR;
            args >> depthLR;
	    printf("low resolution is %d %d %d\n", widthLR, heightLR, depthLR);
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
    vol1 = new volume(widthLR, heightLR, depthLR);
    vol2 = new volume(widthLR, heightLR, depthLR);

    vol3 = new volume(widthHR, heightHR, depthHR);
    vol4 = new volume(widthHR, heightHR, depthHR);

    imageBufferTarget = new unsigned char[widthHR*heightHR*depthHR];
    if(!imageBufferTarget)
    {
	printf("new buffer failed\n");
    }
    printf("image buffer pointer is %ul\n", imageBufferTarget);
    printf("vol2 pointer is %ul\n", vol2);

    unsigned char *data = readRAWfile((char *)rawfnHR.c_str(), &size);
    printf("data pointer is %ul\n", (unsigned long)data);
    for(int i=0; i<widthHR*heightHR*depthHR; i++ )
	vol3->set_dat_from_ind(data[i], i);
    delete data;

    data = readRAWfile((char *)rawfnLR.c_str(), &size);
    for(int i=0; i<widthLR*heightLR*depthLR; i++ )
	vol1->set_dat_from_ind(data[i], i);

    delete data;

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
    delete[] imageBufferTarget;
     close(sockfd);
     printf("close the server socket\n");
     pthread_exit(NULL);
     return 0; /* we never get here */
}
