//
//  db_class.h
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#ifndef _db_class_h
#define _db_class_h
#include<cmath>
#include "trilinear_class.h"
#include "affine_class.h"

// computes positive integer powers
inline unsigned long intpow(unsigned long b,unsigned long e) {
	unsigned long r=1;
	for (unsigned long i=0;i<e;i++) {
		r*=b;
	}
	return r;
} 
 
class deBruijn{
private:
	unsigned long base,length,index,temp_index,sequence_length;
	bool completed_sequence;
	unsigned char* a,* temp;
public:
	deBruijn(unsigned long b, unsigned long l): base(b), length(l), index(l), temp_index(1), sequence_length((unsigned long) intpow(b,l)), completed_sequence(false), a(new unsigned char[l+1]), temp(new unsigned char[l+1]) {
		for (int i=0;i<l+1;i++) {a[i]=0;temp[i]=0;};
		//temp[1]=0;
	}
	~deBruijn() {
		delete[] a;
		delete[] temp;
	}
	unsigned char next() {
		if (temp_index>0) {
			return temp[temp_index--];
		} else {
			int j;
			while (index>0) {
				a[index]++;
				for (j=1;j<length-index+1;j++) a[j+index]=a[j];
				if (length%index==0) {
					for (j=1;j<index+1;j++) {
						temp[index+1-j]=a[j];
					}
					temp_index=index;
					index=length;
					while (a[index]==base-1) index--;
					return temp[temp_index--];
				}
				index=length;
				while (a[index]==base-1) index--;
			}
			completed_sequence=true;
			reset();
			return temp[temp_index--]; //this is initial 0 of next loop
		}
	}
	void skip(unsigned long num_skip) {
		int j;
		unsigned long i=0;
		while (temp_index>0) {
			next();
			i++;
		}
		while (i<num_skip-2*length) { // proceed within 2*length to be safe
			while (index>0) {
				a[index]++;
				for (j=1;j<length-index+1;j++) a[j+index]=a[j];
				if (length%index==0) {
					i+=(unsigned long)index;
				}
				index=length;
				while (a[index]==base-1) index--;
				if (i>=num_skip-2*length) break;
			}
			if (index==0) {
				completed_sequence=true;
				reset();
				i++; //not 100% sure about this one
			};
		}
		// we proceed the last length steps making sure temp[] is updated
		while (i<num_skip) {
			next();
			i++;
		}
		return ; 
	}
	int reset() {
		for (int i=0;i<length+1;i++) {a[i]=0;temp[i]=0;};
		index=length;
		temp_index=1;
		//temp[1]=0;
		return 0;
	}
	bool check_completion_flag() {return completed_sequence;};
	int reset_completion_flag() {completed_sequence=false;return 0;};
	unsigned long get_seq_len() {return sequence_length;};
	void dump_state(int* vec) {
		for (int i=0;i<length+1;i++) {
			vec[i]=(int)a[i];
			vec[length+1+i]=(int)temp[i];
		}
		vec[2*(length+1)]=index;
		vec[2*(length+1)+1]=temp_index;
	};
	void set_state(int* vec) {
		for (int i=0;i<length+1;i++) {
			a[i]=(unsigned char)vec[i];
			temp[i]=(unsigned char)vec[length+1+i];
		}
		index=vec[2*(length+1)];
		temp_index=vec[2*(length+1)+1];
	};
};

unsigned int db_chaos_parallel(trilinearIFS ifs1,volume* vol1,trilinearIFS ifs2,volume* vol2,unsigned int its_mult);
unsigned long db_chaos_parallel_8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult);
unsigned long db_chaos_parallel_8tetra_safe(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult);
unsigned long db_chaos_parallel_large_6x8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult);
unsigned long db_chaos_parallel_large_6x8tetra_alt(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult);
unsigned long db_chaos_parallel_large_5x8tetra(affineIFS ifs1,volume* vol1,affineIFS ifs2,volume* vol2,unsigned long its_mult);

#endif
