//
//  affine_class.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _affine_class_h

#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<inttypes.h>

const double TOLERANCE=1.0e-6;

// class for a volumetric data slab
class volume{
private:
	uint64_t dim[3];
	unsigned char* slab;
public:
	volume(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=(uint64_t) wid;
		dim[1]=(uint64_t) hei;
		dim[0]=(uint64_t) dep;
		slab=new unsigned char[wid*hei*dep];
		for (uint64_t i=0;i<wid*hei*dep;i++) slab[i]=0;
	}
	~volume(){
		if (dim[0]*dim[1]*dim[2]>0) delete slab;
	}
	uint64_t get_size(){
		return dim[0]*dim[1]*dim[2];
	};
	unsigned int get_wid() {
		return (unsigned int) dim[2];
	}
	unsigned int get_hei() {
		return (unsigned int) dim[1];
	}
	unsigned int get_dep() {
		return (unsigned int) dim[0];
	}
	void fill(unsigned char value) {
		for (uint64_t i=0;i<dim[0]*dim[1]*dim[2];i++) slab[i]=value;
	}
	unsigned char get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		uint64_t index=(uint64_t) (k*dim[1]+j)*dim[2]+i;
		return slab[index];
	}
	unsigned char get_dat_from_ind(uint64_t ind) {
		return slab[ind];
	}
	void set_dat_from_coord(unsigned char value, unsigned int i,unsigned int j, unsigned int k) {
		uint64_t index=(uint64_t) (k*dim[1]+j)*dim[2]+i;
		slab[index]=value;
	}
	void set_dat_from_ind(unsigned char value,uint64_t ind) {
		slab[ind]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		uint64_t index=(uint64_t) (k*dim[1]+j)*dim[2]+i;
		if (slab[index]<255) slab[index]++;
	}
	void increment_ind(uint64_t ind) {
		if (slab[ind]<255) slab[ind]++;
	}
	uint64_t sum() {
		uint64_t s=0;
		for (uint64_t i=0;i<dim[0]*dim[1]*dim[2];i++) s+=slab[i];
		return s;
	}
	uint64_t num_more_than(unsigned char a) {
		uint64_t s=0;
		for (uint64_t i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]>a) s++;
		return s;
	}
	uint64_t num_non_zero() {
		return num_more_than(0);
	}
	uint64_t num_less_than(unsigned char a) {
		uint64_t s=0;
		for (uint64_t i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]<a) s++;
		return s;
	}
	void add_sphere(double rad,double* cen,unsigned char value=255) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		uint64_t m,n;
		for (uint64_t k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			m=k*dim[1];
			for (uint64_t j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=(m+j)*dim[2];
				for (uint64_t i=0;i<dim[2];i++) {
					x=1.0*i/(dim[2]-1);
					x2=(x-cen[0])*(x-cen[0]);
					if (x2+y2+z2<=rad2) slab[n+i]=value;
				}
			}
		}
	}
	void save(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		if (!fp) {
			printf("ERROR: volume.save: could not save volume\n");
			return;
		}
		// first byte is the bytes per data point
		unsigned char header=1;
		fwrite(&header,sizeof(unsigned char),1,fp);
		// next 12 bytes is the dimensions
		unsigned int dim32[3];
		dim32[0]=(unsigned int) dim[0];
		dim32[1]=(unsigned int) dim[1];
		dim32[2]=(unsigned int) dim[2];
		fwrite(dim32,sizeof(unsigned int),3,fp);
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fwrite(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned char* ptr=slab;
		for (unsigned int i=0;i<dim32[0];i++) {
			fwrite(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
			ptr+=dim32[1]*dim32[2];
		}
		fclose(fp);
	}
	void load(char* filename) {
		FILE* fp;
		fp=fopen(filename,"rb");
		if (!fp) {
			printf("ERROR: volume.load: could not load volume\n");
			return;
		}
		// first byte is the bytes per data point
		unsigned char header;
		fread(&header,sizeof(unsigned char),1,fp);
		// the header byte should be 0 or 1 for this format
		if (header>1) {
			printf("volume: load: header byte is incorrect for this format (expected 0 or 1, got %d)\n",(int)header);
			fclose(fp);
			return;
		}
		// first 12 bytes is the dimensions
		unsigned int dim32[3];
		fread(dim32,sizeof(unsigned int),3,fp);
		dim[0]=(uint64_t) dim32[0];
		dim[1]=(uint64_t) dim32[1];
		dim[2]=(uint64_t) dim32[2];
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fread(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned char* ptr=slab;
		for (unsigned int i=0;i<dim32[0];i++) {
			fread(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
			ptr+=dim32[1]*dim32[2];
		}
		fclose(fp);
	}
};

// class for a volumetric data slab
class large_volume{
private:
	uint64_t dim[3];
	unsigned char** slab;
public:
	large_volume(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=(uint64_t) wid;
		dim[1]=(uint64_t) hei;
		dim[0]=(uint64_t) dep;
		//slab=new unsigned char[wid*hei*dep];
		if (dim[2]*dim[1]*dim[0]>0) {
			slab=new unsigned char*[dep];
			for (uint64_t k=0;k<dim[0];k++) {
				slab[k]=new unsigned char[dim[1]*dim[2]];
				for (uint64_t i=0;i<dim[1]*dim[2];i++) slab[k][i]=0;
			}
		}
	}
	~large_volume(){
		if (dim[0]*dim[1]*dim[2]>0) {
			for (uint64_t k=0;k<dim[0];k++) {
				delete [] slab[k];
			};
			delete [] slab;
		}
	}
	uint64_t get_size(){
		return dim[0]*dim[1]*dim[2];
	};
	unsigned int get_wid() {
		return (unsigned int) dim[2];
	}
	unsigned int get_hei() {
		return (unsigned int) dim[1];
	}
	unsigned int get_dep() {
		return (unsigned int) dim[0];
	}
	void fill(unsigned char value) {
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) slab[k][i]=value;
		}
	}
	unsigned char get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		return slab[k][j*dim[2]+i];
	}
	unsigned char get_dat_from_ind(uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		return slab[k][index];
	}
	void set_dat_from_coord(unsigned char value, unsigned int i,unsigned int j, unsigned int k) {
		slab[k][j*dim[2]+i]=value;
	}
	void set_dat_from_ind(unsigned char value,uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		slab[k][index]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		uint64_t index=(uint64_t) j*dim[2]+i;
		if (slab[k][index]<255) slab[k][index]++;
	}
	void increment_ind(uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		if (slab[k][index]<255) slab[k][index]++;
	}
	uint64_t sum() {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) s+=slab[k][i];
		}
		return s;
	}
	uint64_t num_more_than(unsigned char a) {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) if (slab[k][i]>a) s++;
		}
		return s;
	}
	uint64_t num_non_zero() {
		return num_more_than(0);
	}
	uint64_t num_less_than(unsigned char a) {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) if (slab[k][i]<a) s++;
		}
		return s;
	}
	unsigned char** get_slices_ptr() {
		return slab;
	};
	void add_sphere(double rad,double* cen,unsigned char value=255) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		uint64_t n;
		for (uint64_t k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			for (uint64_t j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=j*dim[2];
				for (uint64_t i=0;i<dim[2];i++) {
					x=1.0*i/(dim[2]-1);
					x2=(x-cen[0])*(x-cen[0]);
					if (x2+y2+z2<=rad2) slab[k][n+i]=value;
				}
			}
		}
	}
	void save(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		// first byte is the bytes per data point
		unsigned char header=1;
		fwrite(&header,sizeof(unsigned char),1,fp);
		// next 12 bytes is the dimensions
		unsigned int dim32[3];
		dim32[0]=(unsigned int) dim[0];
		dim32[1]=(unsigned int) dim[1];
		dim32[2]=(unsigned int) dim[2];
		fwrite(dim32,sizeof(unsigned int),3,fp);
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fwrite(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned char* ptr;
		for (uint64_t k=0;k<dim[0];k++) {
			ptr=slab[k];
			fwrite(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
		}
		fclose(fp);
	}
	void load(char* filename) {
		// Note that you need to allocate the volume with correct dimensions 
		// before loading the data
		// THIS SHOULD PROBABLY BE EXTENDED TO RE-ALLOCATE DATA
		FILE* fp;
		fp=fopen(filename,"rb");
		// first byte is the bytes per data point
		unsigned char header;
		fread(&header,sizeof(unsigned char),1,fp);
		// the header byte should be 0 or 1 for this format
		if (header>1) {
			printf("volume: load: header byte is incorrect for this format (expected 0 or 1, got %d)\n",(int)header);
			fclose(fp);
			return;
		}
		// first 12 bytes is the dimensions
		unsigned int dim32[3];
		fread(dim32,sizeof(unsigned int),3,fp);
		// now check if the correct size has already been allocated, otherwise allocate it.
		if (dim32[0]!=(unsigned int)dim[0] || dim32[1]!=(unsigned int)dim[1] ||  dim32[2]!=(unsigned int)dim[2]) {
			printf("volume.load: allocating volume of size: %u,%u,%u\n",dim32[0],dim32[1],dim32[2]);
			if (dim[0]*dim[1]*dim[2]>0) {
				for (uint64_t k=0;k<dim[0];k++) {
					delete [] slab[k];
				};
				delete [] slab;
			}
			dim[0]=(uint64_t) dim32[0];
			dim[1]=(uint64_t) dim32[1];
			dim[2]=(uint64_t) dim32[2];
			if (dim[2]*dim[1]*dim[0]>0) {
				slab=new unsigned char*[dim[2]];
				for (uint64_t k=0;k<dim[0];k++) {
					slab[k]=new unsigned char[dim[1]*dim[2]];
				}
			}
		}
		// now the data
		unsigned char* ptr;
		for (uint64_t k=0;k<dim[0];k++) {
			ptr=slab[k];
			fread(ptr,sizeof(unsigned char),dim32[1]*dim32[2],fp);
		}
		fclose(fp);
	}
};

// class for a volumetric data slab
class large_volume_shorts{
private:
	uint64_t dim[3];
	unsigned short** slab;
public:
	large_volume_shorts(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=(uint64_t) wid;
		dim[1]=(uint64_t) hei;
		dim[0]=(uint64_t) dep;
		//slab=new unsigned short[wid*hei*dep];
		slab=new unsigned short*[dep];
		for (uint64_t k=0;k<dim[0];k++) {
			slab[k]=new unsigned short[dim[1]*dim[2]];
			for (uint64_t i=0;i<dim[1]*dim[2];i++) slab[k][i]=0;
		}
	}
	~large_volume_shorts(){
		if (dim[0]*dim[1]*dim[2]>0) {
			for (uint64_t k=0;k<dim[0];k++) {
				delete [] slab[k];
			};
			delete [] slab;
		}
	}
	uint64_t get_size(){
		return dim[0]*dim[1]*dim[2];
	};
	unsigned int get_wid() {
		return (unsigned int) dim[2];
	}
	unsigned int get_hei() {
		return (unsigned int) dim[1];
	}
	unsigned int get_dep() {
		return (unsigned int) dim[0];
	}
	void fill(unsigned short value) {
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) slab[k][i]=value;
		}
	}
	unsigned short get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		return slab[k][j*dim[2]+i];
	}
	unsigned short get_dat_from_ind(uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		return slab[k][index];
	}
	void set_dat_from_coord(unsigned short value, unsigned int i,unsigned int j, unsigned int k) {
		slab[k][j*dim[2]+i]=value;
	}
	void set_dat_from_ind(unsigned short value,uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		slab[k][index]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		uint64_t index=(uint64_t) j*dim[2]+i;
		if (slab[k][index]<255) slab[k][index]++;
	}
	void increment_ind(uint64_t ind) {
		uint64_t index = ind%(dim[1]*dim[2]);
		uint64_t k = (uint64_t) ind/(dim[1]*dim[2]);
		if (slab[k][index]<255) slab[k][index]++;
	}
	uint64_t sum() {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) s+=slab[k][i];
		}
		return s;
	}
	uint64_t num_more_than(unsigned short a) {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) if (slab[k][i]>a) s++;
		}
		return s;
	}
	uint64_t num_non_zero() {
		return num_more_than(0);
	}
	uint64_t num_less_than(unsigned short a) {
		uint64_t s=0;
		for (uint64_t k=0;k<dim[0];k++) {
			for (uint64_t i=0;i<dim[1]*dim[2];i++) if (slab[k][i]<a) s++;
		}
		return s;
	}
	void add_sphere(double rad,double* cen,unsigned short value=65535) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		uint64_t n;
		for (uint64_t k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			for (uint64_t j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=j*dim[2];
				for (uint64_t i=0;i<dim[2];i++) {
					x=1.0*i/(dim[2]-1);
					x2=(x-cen[0])*(x-cen[0]);
					if (x2+y2+z2<=rad2) slab[k][n+i]=value;
				}
			}
		}
	}
	void save(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		// first byte is the bytes per data point
		unsigned char header=2;
		fwrite(&header,sizeof(unsigned char),1,fp);
		// next 12 bytes is the dimensions
		unsigned int dim32[3];
		dim32[0]=(unsigned int) dim[0];
		dim32[1]=(unsigned int) dim[1];
		dim32[2]=(unsigned int) dim[2];
		fwrite(dim32,sizeof(unsigned int),3,fp);
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fwrite(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned short* ptr;
		for (uint64_t k=0;k<dim[0];k++) {
			ptr=slab[k];
			fwrite(ptr,sizeof(unsigned short),dim32[1]*dim32[2],fp);
		}
		fclose(fp);
	}
	void load(char* filename) {
		// Note that you need to allocate the volume with correct dimensions
		// before loading the data
		// THIS SHOULD PROBABLY BE EXTENDED TO RE-ALLOCATE DATA
		FILE* fp;
		fp=fopen(filename,"rb");
		// first byte is the bytes per data point
		unsigned char header;
		fread(&header,sizeof(unsigned char),1,fp);
		// the header byte should be 2 for this format
		if (header!=2) {
			printf("volume: load: header byte is incorrect for this format (expected 2, got %d)\n",(int)header);
			fclose(fp);
			return;
		}
		// first 12 bytes is the dimensions
		unsigned int dim32[3];
		fread(dim32,sizeof(unsigned int),3,fp);
		dim[0]=(uint64_t) dim32[0];
		dim[1]=(uint64_t) dim32[1];
		dim[2]=(uint64_t) dim32[2];
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fread(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned short* ptr;
		for (uint64_t k=0;k<dim[0];k++) {
			ptr=slab[k];
			fread(ptr,sizeof(unsigned short),dim32[1]*dim32[2],fp);
		}
		fclose(fp);
	}
};

// class for a vertex array
class vertices{
private:
	unsigned int num_vertices;
	double* verts;
public:
	vertices(unsigned int len) {
		num_vertices=len;
		verts=new double[3*num_vertices];
		for (unsigned int i=0;i<3*num_vertices;i++) verts[i]=0.0;
	}
	~vertices(){
		if (num_vertices>0) delete verts;
	}
	unsigned int get_size(){
		return num_vertices;
	};
	double* get_vertex_ptr(unsigned int ind) {
		return &verts[3*ind];
	}
	void get_vertex(unsigned int ind,double* vertex) {
		for (unsigned int i=0;i<3;i++) vertex[i]=verts[3*ind+i];
	}
	void set_vertex(unsigned int ind,double* vertex) {
		for (unsigned int i=0;i<3;i++) verts[3*ind+i]=vertex[i];
	}
	void fill_rand() {
		//fills array with random points, useful for testing
		for (unsigned int i=0;i<3*num_vertices;i++) {
			verts[i]=1.0*rand()/RAND_MAX;
		}
	}
	/*
	// should add routine for saving/loading as a binary stl file
	// this would assume that the vertices are a list of triangles
	// in particular, num_vertices should be a multiple of 3
	// we also need to calculate normals
	void save_stl(char* filename) {
		FILE* fp;
		fp=fopen(filename,"wb");
		//..........
		fclose(fp);
	}
	void load_stl(char* filename) {
		FILE* fp;
		fp=fopen(filename,"rb");
		//..........
		fclose(fp);
	}
	*/
};

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

// Operators on 2 IFSs:
// chaos game transform (for volumetric data)
void chaos(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned int its_mult=4) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: chaos: both IFSs must have the same length>0\n");
		return;
	}
	int num_fns=ifs1.len();
	// vol1 is mapped to vol2 where ifs1 is the 'colour stealing' IFS
	unsigned int its=its_mult*vol2->get_size();
	vol2->fill((unsigned char)0);
	unsigned int wid1=vol1->get_wid();
	unsigned int hei1=vol1->get_hei();
	unsigned int dep1=vol1->get_dep();
	unsigned int wid2=vol2->get_wid();
	unsigned int hei2=vol2->get_hei();
	unsigned int dep2=vol2->get_dep();
	unsigned int ix1[3],ix2[3];
	int ran;
	double x1[3],y1[3],x2[3],y2[3];
	x1[0]=0.5;x1[1]=0.5;x1[2]=0.5;
	x2[0]=0.5;x2[1]=0.5;x2[2]=0.5;
	int ranD=1+RAND_MAX/num_fns;
	for (unsigned int it=0;it<its;it++) {
		ran=rand()/ranD;
		ifs1.apply_fn(ran,x1,y1);
		ifs2.apply_fn(ran,x2,y2);
		x1[0]=y1[0];x1[1]=y1[1];x1[2]=y1[2];
		x2[0]=y2[0];x2[1]=y2[1];x2[2]=y2[2];
		ix1[0]=0.5+x1[0]*(wid1-1);
		ix1[1]=0.5+x1[1]*(hei1-1);
		ix1[2]=0.5+x1[2]*(dep1-1);
		ix2[0]=0.5+x2[0]*(wid2-1);
		ix2[1]=0.5+x2[1]*(hei2-1);
		ix2[2]=0.5+x2[2]*(dep2-1);
		vol2->set_dat_from_coord(vol1->get_dat_from_coord(ix1[0],ix1[1],ix1[2]),ix2[0],ix2[1],ix2[2]);
	}
}

// deterministic transform (for a list of points, e.g. mesh coordinates)
void deterministic(affineIFS ifs1,vertices* verts1,affineIFS ifs2,vertices* verts2,int codelength=20) {
	if (ifs1.len()!=ifs2.len() || ifs1.len()==0) {
		printf("ERROR: deterministic: both IFSs must have the same length>0\n");
		return;
	}
	if (verts1->get_size()!=verts2->get_size()) {
		printf("ERROR: deterministic: both vertices objects must have the same length\n");
		return;
	}
	unsigned int num_verts=verts1->get_size();
	double x[3],y[3];
	int code[codelength];
	for (unsigned int i=0;i<num_verts;i++) {
		verts1->get_vertex(i,x);
		for (int k=0;k<codelength;k++) {
			code[k]=ifs2.find_domain_and_invert(x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		for (int k=codelength-1;k>=0;k--) {
			ifs1.apply_fn(code[k],x,y);
			x[0]=y[0];x[1]=y[1];x[2]=y[2];
		}
		verts2->set_vertex(i,x);
	}
}

#define _affine_class_h



#endif
