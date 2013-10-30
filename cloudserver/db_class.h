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

/*
 db_state_lookup_b8_ll5_ul10_s8:
 -> b8 for base 8, s8 for 8 evenly spaced samples
 -> ll5 for lower length 5, ul10 for upper length 10
 -> length of lookup is hence (10-5+1)*8*24=1152
 Actually, renamed without all of the silly bits.
 To access a state, say 5th state of length 7 sequence:
 -> take 7-5+1=3, 3*8 is 24,
 this is the starting index of length 7 states
 -> now the 5th state is at the 24+(5-1)=28th position
 -> the length of the state is 2*(7+2)=18,
 the max length of the states is 24 so array of this length is OK
 */
//static const int db_state_lookup_b8_ll5_ul10_s8[]={
static const int db8_lookup[1152]={
	0,0,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,6,6,6,0,6,6,6,1,0,5,0,0,0,0,0,0,0,0,0,0,0,
	0,0,3,6,5,5,0,5,5,6,3,0,5,4,0,0,0,0,0,0,0,0,0,0,
	0,0,5,7,5,1,0,1,5,7,5,0,5,3,0,0,0,0,0,0,0,0,0,0,
	0,1,1,3,1,2,0,2,1,3,1,1,5,3,0,0,0,0,0,0,0,0,0,0,
	0,1,4,2,7,2,0,2,7,2,4,1,5,2,0,0,0,0,0,0,0,0,0,0,
	0,1,7,5,6,2,0,2,6,5,7,1,5,1,0,0,0,0,0,0,0,0,0,0,
	0,2,6,5,5,5,0,5,5,5,6,2,5,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,0,0,0,0,0,0,0,0,
	0,0,1,4,4,1,3,0,3,1,4,4,1,0,6,4,0,0,0,0,0,0,0,0,
	0,0,3,2,1,3,2,0,2,3,1,2,3,0,6,0,0,0,0,0,0,0,0,0,
	0,0,5,1,1,0,7,0,7,0,1,1,5,0,5,5,0,0,0,0,0,0,0,0,
	0,0,7,1,4,5,7,0,7,5,4,1,7,0,5,1,0,0,0,0,0,0,0,0,
	0,1,2,5,3,4,7,0,7,4,3,5,2,1,5,2,0,0,0,0,0,0,0,0,
	0,1,5,6,5,4,6,0,6,4,5,6,5,1,6,3,0,0,0,0,0,0,0,0,
	0,2,4,3,7,6,5,0,5,6,7,3,4,2,6,4,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,0,0,0,0,0,0,
	0,0,1,2,6,3,4,5,0,5,4,3,6,2,1,0,7,0,0,0,0,0,0,0,
	0,0,2,6,3,5,0,3,0,3,0,5,3,6,2,0,7,6,0,0,0,0,0,0,
	0,0,4,3,4,5,4,3,0,3,4,5,4,3,4,0,7,5,0,0,0,0,0,0,
	0,0,6,2,3,2,3,6,0,6,3,2,3,2,6,0,7,4,0,0,0,0,0,0,
	0,1,1,3,5,1,7,7,0,7,7,1,5,3,1,1,5,4,0,0,0,0,0,0,
	0,1,4,3,4,4,2,5,0,5,2,4,4,3,4,1,7,3,0,0,0,0,0,0,
	0,2,2,4,4,3,5,3,0,3,5,3,4,4,2,2,7,3,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1,0,0,0,0,
	0,0,1,1,4,0,6,7,7,0,7,7,6,0,4,1,1,0,6,3,0,0,0,0,
	0,0,2,3,6,7,2,2,4,0,4,2,2,7,6,3,2,0,8,5,0,0,0,0,
	0,0,3,7,2,2,5,6,5,0,5,6,5,2,2,7,3,0,8,3,0,0,0,0,
	0,0,5,4,4,7,6,5,5,0,5,5,6,7,4,4,5,0,8,7,0,0,0,0,
	0,0,7,4,1,7,6,4,4,0,4,4,6,7,1,4,7,0,8,3,0,0,0,0,
	0,1,3,2,1,3,2,2,5,0,5,2,2,3,1,2,3,1,8,0,0,0,0,0,
	0,1,6,7,6,4,4,4,2,0,2,4,4,4,6,7,6,1,8,2,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,1,0,0,
	0,0,1,0,3,7,3,7,3,5,0,5,3,7,3,7,3,0,1,0,9,3,0,0,
	0,0,2,1,6,4,5,0,6,7,0,7,6,0,5,4,6,1,2,0,8,8,0,0,
	0,0,3,4,1,6,5,5,4,1,0,1,4,5,5,6,1,4,3,0,9,1,0,0,
	0,0,4,7,7,2,0,7,7,6,0,6,7,7,0,2,7,7,4,0,9,3,0,0,
	0,0,6,6,2,3,6,0,7,7,0,7,7,0,6,3,2,6,6,0,7,5,0,0,
	0,1,2,1,7,5,2,1,3,7,0,7,3,1,2,5,7,1,2,1,8,2,0,0,
	0,1,5,6,5,4,6,3,6,2,0,2,6,3,6,4,5,6,5,1,9,7,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,1,
	0,0,0,7,4,4,0,2,4,0,2,0,2,0,4,2,0,4,4,7,0,0,10,3,
	0,0,1,7,7,3,3,6,3,4,3,0,3,4,3,6,3,3,7,7,1,0,10,7,
	0,0,3,1,5,4,1,1,5,5,5,0,5,5,5,1,1,4,5,1,3,0,10,8,
	0,0,4,4,4,3,7,7,6,2,5,0,5,2,6,7,7,3,4,4,4,0,10,2,
	0,0,6,1,7,6,2,3,6,3,2,0,2,3,6,3,2,6,7,1,6,0,10,8,
	0,1,1,3,1,1,6,3,5,7,3,0,3,7,5,3,6,1,1,3,1,1,10,8,
	0,1,4,6,4,4,7,4,7,6,5,0,5,6,7,4,7,4,4,6,4,1,10,6
};

//This includes the last 10 values at the end
static const int db8_lookup2[1632]={
	0,0,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,7,7,
	0,0,1,6,6,6,0,6,6,6,1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1,6,6,5,0,1,6,6,6,
	0,0,3,6,5,5,0,5,5,6,3,0,5,4,0,0,0,0,0,0,0,0,0,0,3,6,5,3,0,3,6,5,4,0,
	0,0,5,7,5,1,0,1,5,7,5,0,5,3,0,0,0,0,0,0,0,0,0,0,7,4,6,0,5,7,4,7,0,5,
	0,1,1,3,1,2,0,2,1,3,1,1,5,3,0,0,0,0,0,0,0,0,0,0,2,7,6,1,1,2,7,7,1,1,
	0,1,4,2,7,2,0,2,7,2,4,1,5,2,0,0,0,0,0,0,0,0,0,0,6,6,1,4,2,6,7,1,4,2,
	0,1,7,5,6,2,0,2,6,5,7,1,5,1,0,0,0,0,0,0,0,0,0,0,6,1,7,5,5,7,1,7,5,6,
	0,2,6,5,5,5,0,5,5,5,6,2,5,1,0,0,0,0,0,0,0,0,0,0,3,2,6,5,5,4,2,6,5,5,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,7,7,
	0,0,1,4,4,1,3,0,3,1,4,4,1,0,6,4,0,0,0,0,0,0,0,0,1,1,0,1,4,4,1,2,0,1,
	0,0,3,2,1,3,2,0,2,3,1,2,3,0,6,0,0,0,0,0,0,0,0,0,2,1,3,1,0,3,2,1,3,2,
	0,0,5,1,1,0,7,0,7,0,1,1,5,0,5,5,0,0,0,0,0,0,0,0,0,7,7,0,5,1,1,0,6,0,
	0,0,7,1,4,5,7,0,7,5,4,1,7,0,5,1,0,0,0,0,0,0,0,0,7,1,4,5,6,0,7,1,4,5,
	0,1,2,5,3,4,7,0,7,4,3,5,2,1,5,2,0,0,0,0,0,0,0,0,1,2,5,3,4,6,1,2,5,3,
	0,1,5,6,5,4,6,0,6,4,5,6,5,1,6,3,0,0,0,0,0,0,0,0,4,1,5,6,5,4,5,1,5,6,
	0,2,4,3,7,6,5,0,5,6,7,3,4,2,6,4,0,0,0,0,0,0,0,0,6,3,2,4,3,7,6,4,2,4,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,0,0,0,0,0,0,7,7,7,7,7,7,7,7,7,7,
	0,0,1,2,6,3,4,5,0,5,4,3,6,2,1,0,7,0,0,0,0,0,0,0,3,4,4,0,1,2,6,3,4,5,
	0,0,2,6,3,5,0,3,0,3,0,5,3,6,2,0,7,6,0,0,0,0,0,0,7,6,0,2,6,3,4,7,7,0,
	0,0,4,3,4,5,4,3,0,3,4,5,4,3,4,0,7,5,0,0,0,0,0,0,1,0,4,3,4,5,4,2,0,4,
	0,0,6,2,3,2,3,6,0,6,3,2,3,2,6,0,7,4,0,0,0,0,0,0,0,6,2,3,2,3,5,0,6,2,
	0,1,1,3,5,1,7,7,0,7,7,1,5,3,1,1,5,4,0,0,0,0,0,0,1,1,3,5,1,7,6,1,1,3,
	0,1,4,3,4,4,2,5,0,5,2,4,4,3,4,1,7,3,0,0,0,0,0,0,4,3,4,4,2,4,1,4,3,4,
	0,2,2,4,4,3,5,3,0,3,5,3,4,4,2,2,7,3,0,0,0,0,0,0,2,4,4,3,4,7,2,2,4,4,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1,0,0,0,0,7,7,7,7,7,7,7,7,7,7,
	0,0,1,1,4,0,6,7,7,0,7,7,6,0,4,1,1,0,6,3,0,0,0,0,4,0,6,7,6,0,1,1,4,0,
	0,0,2,3,6,7,2,2,4,0,4,2,2,7,6,3,2,0,8,5,0,0,0,0,2,3,6,7,2,2,3,0,2,3,
	0,0,3,7,2,2,5,6,5,0,5,6,5,2,2,7,3,0,8,3,0,0,0,0,2,2,5,6,4,0,3,7,2,2,
	0,0,5,4,4,7,6,5,5,0,5,5,6,7,4,4,5,0,8,7,0,0,0,0,3,0,5,4,4,7,6,5,4,0,
	0,0,7,4,1,7,6,4,4,0,4,4,6,7,1,4,7,0,8,3,0,0,0,0,1,7,6,4,3,0,7,4,1,7,
	0,1,3,2,1,3,2,2,5,0,5,2,2,3,1,2,3,1,8,0,0,0,0,0,2,4,1,3,2,1,3,2,2,5,
	0,1,6,7,6,4,4,4,2,0,2,4,4,4,6,7,6,1,8,2,0,0,0,0,4,4,3,7,1,6,7,6,4,4,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,1,0,0,7,7,7,7,7,7,7,7,7,7,
	0,0,1,0,3,7,3,7,3,5,0,5,3,7,3,7,3,0,1,0,9,3,0,0,3,7,3,4,0,1,0,3,7,3,
	0,0,2,1,6,4,5,0,6,7,0,7,6,0,5,4,6,1,2,0,8,8,0,0,0,2,1,6,4,5,0,6,6,0,
	0,0,3,4,1,6,5,5,4,1,0,1,4,5,5,6,1,4,3,0,9,1,0,0,3,7,0,3,4,1,6,5,5,4,
	0,0,4,7,7,2,0,7,7,6,0,6,7,7,0,2,7,7,4,0,9,3,0,0,0,7,7,5,0,4,7,7,2,0,
	0,0,6,6,2,3,6,0,7,7,0,7,7,0,6,3,2,6,6,0,7,5,0,0,2,3,6,0,7,6,0,6,6,2,
	0,1,2,1,7,5,2,1,3,7,0,7,3,1,2,5,7,1,2,1,8,2,0,0,1,3,6,1,2,1,7,5,2,1,
	0,1,5,6,5,4,6,3,6,2,0,2,6,3,6,4,5,6,5,1,9,7,0,0,5,6,5,4,6,3,5,7,1,5,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,1,7,7,7,7,7,7,7,7,7,7,
	0,0,0,7,4,4,0,2,4,0,2,0,2,0,4,2,0,4,4,7,0,0,10,3,4,0,1,0,0,7,4,4,0,2,
	0,0,1,7,7,3,3,6,3,4,3,0,3,4,3,6,3,3,7,7,1,0,10,7,7,3,3,6,3,4,2,0,1,7,
	0,0,3,1,5,4,1,1,5,5,5,0,5,5,5,1,1,4,5,1,3,0,10,8,1,5,4,1,1,5,5,4,0,3,
	0,0,4,4,4,3,7,7,6,2,5,0,5,2,6,7,7,3,4,4,4,0,10,2,2,4,0,4,4,4,3,7,7,6,
	0,0,6,1,7,6,2,3,6,3,2,0,2,3,6,3,2,6,7,1,6,0,10,8,1,7,6,2,3,6,3,1,0,6,
	0,1,1,3,1,1,6,3,5,7,3,0,3,7,5,3,6,1,1,3,1,1,10,8,3,1,1,6,3,5,7,2,1,1,
	0,1,4,6,4,4,7,4,7,6,5,0,5,6,7,4,7,4,4,6,4,1,10,6,4,7,4,7,6,4,1,4,6,4
};

class deBruijn{
private:
	int sequence_length,base,length,index,temp_index;
	bool completed_sequence;
	unsigned char* a,* temp;
public:
	deBruijn(int b, int l): base(b), length(l), index(l), temp_index(1), sequence_length(pow(b,l)), a(new unsigned char[l+1]), temp(new unsigned char[l+1]), completed_sequence(false) {
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
			return temp[temp_index--]; //this is the initial 0 of the next loop
		}
		completed_sequence=true;
		reset();
		return temp[temp_index--]; //this is the initial zero of the next loop
	}
	int reset() {
		for (int i=0;i<length+1;i++) a[i]=0;
		index=length;
		temp_index=1;
		temp[1]=0;
		return 0;
	}
	bool check_completion_flag() {return completed_sequence;};
	int reset_completion_flag() {completed_sequence=false;return 0;};
	int get_seq_len() {return sequence_length;};
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

#endif
