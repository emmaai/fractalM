############################################
# Make file for building
#
############################################

##### Compiler, tools and options

CC	= gcc 
CXX	= g++ 
CFLAGS	= -O3 -fopenmp 
CXXFLAGS= ${CFLAGS} 
DFLAGS	= -g
INCPATH	= 
LINK	= g++ 
LFLAGS	= -Wl,-O1 -Wl,--as-needed -Wl,--hash-style=gnu -Wl,--sort-common 
LIBS	= -stdc++ -lgomp -lpthread

##### Files

HEADERS	=   chaosgame.h \
	    typedef.h \
	    rwsockthread.h \
	    transfmimg.h \
	    3dtransform.h
SOURCES_SERVER	=	server.c  \
			chaosgame.cpp \
			rwsockthread.cpp \
			transfmimg.cpp \
			fractaltransform.cpp \
			3dtransform.cpp
SOURCES_CLIENT  =	client.c

OBJECTS_SERVER	=	server.o \
			chaosgame.o \
			rwsockthread.o \
			transfmimg.o \
			fractaltransform.o \
			3dtransform.o
OBJECTS_CLIENT	= 	client.o	

TARGET_SERVER	=	server
TARGET_CLIENT	= 	client

##### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

##### Build rules

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(OBJECTS_SERVER)
	$(LINK) $(LFLAGS) -o $(TARGET_SERVER) $(OBJECTS_SERVER) $(LIBS)

$(TARGET_CLIENT): $(OBJECTS_CLIENT)
	$(LINK) $(LFLAGS) -o $(TARGET_CLIENT) $(OBJECTS_CLIENT) $(LIBS)

clean:
	-rm -f $(OBJECTS_CLIENT) $(TARGET_CLIENT) $(OBJECTS_SERVER) $(TARGET_SERVER)

	-rm -f *~ core

