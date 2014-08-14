#ifndef VOLUME_CLASS_H
#define VOLUME_CLASS_H

const double TOLERANCE=1.0e-6;

class volume{
private:
	unsigned long dim[3];
public:
	unsigned char* slab;
	volume(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=(unsigned long) wid;
		dim[1]=(unsigned long) hei;
		dim[0]=(unsigned long) dep;
		slab=new unsigned char[dim[2]*dim[1]*dim[0]];
		for (unsigned long i=0;i<dim[2]*dim[1]*dim[00];i++) slab[i]=0;
	}
	~volume(){
		if (dim[0]*dim[1]*dim[2]>0) delete slab;
	}
	unsigned long get_size(){
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
		for (unsigned long i=0;i<dim[0]*dim[1]*dim[2];i++) slab[i]=value;
	}
	unsigned char get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		unsigned long index=(unsigned long) (k*dim[1]+j)*dim[2]+i;
		return slab[index];
	}
	unsigned char get_dat_from_ind(unsigned long ind) {
		return slab[ind];
	}
	void set_dat_from_coord(unsigned char value, unsigned int i,unsigned int j, unsigned int k) {
		unsigned long index=(unsigned long) (k*dim[1]+j)*dim[2]+i;
		slab[index]=value;
	}
	void set_dat_from_ind(unsigned char value,unsigned long ind) {
		slab[ind]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		unsigned long index=(unsigned long) (k*dim[1]+j)*dim[2]+i;
		if (slab[index]<255) slab[index]++;
	}
	void increment_ind(unsigned long ind) {
		if (slab[ind]<255) slab[ind]++;
	}
	unsigned long sum() {
		unsigned long s=0;
		for (unsigned long i=0;i<dim[0]*dim[1]*dim[2];i++) s+=slab[i];
		return s;
	}
	unsigned long num_more_than(unsigned char a) {
		unsigned long s=0;
		for (unsigned long i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]>a) s++;
		return s;
	}
	unsigned long num_non_zero() {
		return num_more_than(0);
	}
	unsigned long num_less_than(unsigned char a) {
		unsigned long s=0;
		for (unsigned long i=0;i<dim[0]*dim[1]*dim[2];i++) if (slab[i]<a) s++;
		return s;
	}
	void add_sphere(double rad,double* cen,unsigned char value=255) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		unsigned long m,n;
		for (unsigned long k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			m=k*dim[1];
			for (unsigned long j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=(m+j)*dim[2];
				for (unsigned long i=0;i<dim[2];i++) {
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
		dim[0]=(unsigned long) dim32[0];
		dim[1]=(unsigned long) dim32[1];
		dim[2]=(unsigned long) dim32[2];
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
class large_volume_shorts{
private:
	unsigned long dim[3];
	unsigned short** slab;
public:
	large_volume_shorts(unsigned int wid,unsigned int hei,unsigned int dep) {
		dim[2]=(unsigned long) wid;
		dim[1]=(unsigned long) hei;
		dim[0]=(unsigned long) dep;
		//slab=new unsigned short[wid*hei*dep];
		slab=new unsigned short*[dep];
		for (unsigned long k=0;k<dim[0];k++) {
			slab[k]=new unsigned short[dim[1]*dim[2]];
			for (unsigned long i=0;i<dim[1]*dim[2];i++) slab[k][i]=0;
		}
	}
	~large_volume_shorts(){
		if (dim[0]*dim[1]*dim[2]>0) {
			for (unsigned long k=0;k<dim[0];k++) {
				delete [] slab[k];
			};
			delete [] slab;
		}
	}
	unsigned long get_size(){
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
		for (unsigned long k=0;k<dim[0];k++) {
			for (unsigned long i=0;i<dim[1]*dim[2];i++) slab[k][i]=value;
		}
	}
	unsigned short get_dat_from_coord(unsigned int i,unsigned int j, unsigned int k) {
		return slab[k][j*dim[2]+i];
	}
	unsigned short get_dat_from_ind(unsigned long ind) {
		unsigned long index = ind%(dim[1]*dim[2]);
		unsigned long k = (unsigned long) ind/(dim[1]*dim[2]);
		return slab[k][index];
	}
	void set_dat_from_coord(unsigned short value, unsigned int i,unsigned int j, unsigned int k) {
		slab[k][j*dim[2]+i]=value;
	}
	void set_dat_from_ind(unsigned short value,unsigned long ind) {
		unsigned long index = ind%(dim[1]*dim[2]);
		unsigned long k = (unsigned long) ind/(dim[1]*dim[2]);
		slab[k][index]=value;
	}
	void increment_coord(unsigned int i,unsigned int j, unsigned int k) {
		unsigned long index=(unsigned long) j*dim[2]+i;
		if (slab[k][index]<255) slab[k][index]++;
	}
	void increment_ind(unsigned long ind) {
		unsigned long index = ind%(dim[1]*dim[2]);
		unsigned long k = (unsigned long) ind/(dim[1]*dim[2]);
		if (slab[k][index]<255) slab[k][index]++;
	}
	unsigned long sum() {
		unsigned long s=0;
		for (unsigned long k=0;k<dim[0];k++) {
			for (unsigned long i=0;i<dim[1]*dim[2];i++) s+=slab[k][i];
		}
		return s;
	}
	unsigned long num_more_than(unsigned short a) {
		unsigned long s=0;
		for (unsigned long k=0;k<dim[0];k++) {
			for (unsigned long i=0;i<dim[1]*dim[2];i++) if (slab[k][i]>a) s++;
		}
		return s;
	}
	unsigned long num_non_zero() {
		return num_more_than(0);
	}
	unsigned long num_less_than(unsigned short a) {
		unsigned long s=0;
		for (unsigned long k=0;k<dim[0];k++) {
			for (unsigned long i=0;i<dim[1]*dim[2];i++) if (slab[k][i]<a) s++;
		}
		return s;
	}
	void add_sphere(double rad,double* cen,unsigned short value=65535) {
		//adds a sphere to the volume (treating volume as unit cube)
		//handy for making some quick data to transform
		//this is ridiculously slow if compiled without optimisation
		double rad2=rad*rad;
		double x,x2,y,y2,z,z2;
		unsigned long n;
		for (unsigned long k=0;k<dim[0];k++) {
			z=1.0*k/(dim[0]-1);
			z2=(z-cen[2])*(z-cen[2]);
			for (unsigned long j=0;j<dim[1];j++) {
				y=1.0*j/(dim[1]-1);
				y2=(y-cen[1])*(y-cen[1]);
				n=j*dim[2];
				for (unsigned long i=0;i<dim[2];i++) {
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
		for (unsigned long k=0;k<dim[0];k++) {
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
		dim[0]=(unsigned long) dim32[0];
		dim[1]=(unsigned long) dim32[1];
		dim[2]=(unsigned long) dim32[2];
		// now the data
		// THIS NEEDS TO BE DONE IN MULTIPLE PASSES IF THE FILE SIZE IS MORE THAN 4GB
		//fread(slab,sizeof(unsigned char),dim[0]*dim[1]*dim[2],fp);
		unsigned short* ptr;
		for (unsigned long k=0;k<dim[0];k++) {
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

#endif
