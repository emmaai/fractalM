############################################
# Make file for building
#
############################################

##### Compiler, tools and options

CC	= gcc 
CXX	= g++ 
CFLAGS	= -O3 -fopenmp 
CXXFLAGS= ${CFLAGS} $(DFLAGS)
DFLAGS	= -g
INCPATH	= 
LINK	= g++ 
LFLAGS	= -Wl,-O1 -Wl,--as-needed -Wl,--hash-style=gnu -Wl,--sort-common $(DFLAGS)
LIBS	= -stdc++ -lgomp -lpthread

##### Files

HEADERS	=   typedef.h \
	    rwsockthread.h \
	    transfmimg.h \
	    3dtransform.h \
	    ddsbase.h \
	    codebase.h \
	    trilinear_class.h \
	    db_class.h
SOURCES_SERVER	=	server.c  \
			rwsockthread.cpp \
			transfmimg.cpp \
			fractaltransform.cpp \
			3dtransform.cpp \
			ddsbase.cpp \
			trilinear_class.cpp \
			db_chaos_3d_parallel.cpp

OBJECTS_SERVER	=	server.o \
			rwsockthread.o \
			transfmimg.o \
			fractaltransform.o \
			3dtransform.o \
			ddsbase.o \
			trilinear_class.o \
			db_chaos_3d_parallel.o

TARGET_SERVER	=	server

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

all: $(TARGET_SERVER) 

$(TARGET_SERVER): $(OBJECTS_SERVER)
	$(LINK) $(LFLAGS) -o $(TARGET_SERVER) $(OBJECTS_SERVER) $(LIBS)


clean:
	-rm -f $(OBJECTS_SERVER) $(TARGET_SERVER)

	-rm -f *~ core

