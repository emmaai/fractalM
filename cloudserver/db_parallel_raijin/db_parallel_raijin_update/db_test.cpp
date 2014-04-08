//
//  homeo_test.cpp
//  
//
//  Created by Brendan Harding on 28/08/13.
//
//

#include "db_class.h"
#include<stdio.h>



int main(){
	
	int base=4;
	int length=3;
	deBruijn db(base,length);
	
	int seqlen=db.get_seq_len();
	
	int state_len=2*(length+1)+2;
	
	int state0[state_len];
	db.dump_state(state0);
	printf("INIT. STATE\n");
	for (int i=0;i<state_len;i++) {
		printf("%d,",state0[i]);
	}
	printf("END\n");
	
	printf("SEQUENCE\n");
	for (int i=0;i<seqlen;i++) {
		printf("%d,",db.next());
	}
	printf("END\n");
	
	printf("REPEAT\n");
	for (int i=0;i<seqlen;i++) {
		printf("%d,",db.next());
	}
	printf("END\n");
	
	db.dump_state(state0);
	printf("END STATE\n");
	for (int i=0;i<state_len;i++) {
		printf("%d,",state0[i]);
	}
	printf("END\n");
	
	printf("HALF SEQUENCE\n");
	for (int i=0;i<seqlen/2;i++) {
		printf("%d,",db.next());
	}
	printf("END\n");
	
	db.dump_state(state0);
	printf("MID STATE\n");
	for (int i=0;i<state_len;i++) {
		printf("%d,",state0[i]);
	}
	printf("END\n");
	
	deBruijn db2(base,length);
	db2.set_state(state0);
	printf("SECOND HALF SEQUENCE FROM STATE\n");
	for (int i=0;i<seqlen/2;i++) {
		printf("%d,",db2.next());
	}
	printf("END\n");
	
	/*
	 vec2 has length 2*(max_length+1)+2+max_length=3*maxlength+4
	 */
	/*
	// The following builds the table for length 5 to 10 sequences
	int vec2[34];
	for (int l=5;l<11;l++) {
		deBruijn db3(8,l);
		int sld8=db3.get_seq_len()/8;
		for (int i=0;i<34;i++) vec2[i]=7;
		for (int j=0;j<8;j++) {
			for (int i=0;i<24;i++) vec2[i]=0;
			db3.dump_state(vec2);
			for (int i=0;i<34;i++) printf("%d,",vec2[i]);
			printf("\n");
			for (int i=0;i<sld8-10;i++) db3.next();
			for (int i=0;i<10;i++) vec2[24+i]=db3.next();
		}
	}
	 */
	
	/*
	deBruijn dbx(8,12);
	int64_t sl=dbx.get_seq_len();
	printf("seq len %"PRId64"\n",sl);
	
	// The following builds the table for length 5 to max_len sequences
	// The length 10 sequence is ~1.1 billion numbers in length
	// It takes 8-9 seconds to generate
	// The length 12 sequence is ~69 billion numbers in length
	// It takes about 8 minutes to generate
	// The length 14 sequence is ~4.4 trillion numbers in length
	// This should take about ~8 hours to generate
	int max_len=14;
	int vec_len=3*max_len+4;
	int dump_len=2*max_len+4;
	int vec2[vec_len];
	printf("numbers per line is %d\n",vec_len);
	printf("number of lines is %d\n",8*(max_len-4));
	for (int l=5;l<=max_len;l++) {
		deBruijn db3(8,l);
		int64_t sld8=db3.get_seq_len()/8;
		for (int i=dump_len;i<vec_len;i++) vec2[i]=7;
		for (int j=0;j<8;j++) {
			for (int i=0;i<dump_len;i++) vec2[i]=0;
			db3.dump_state(vec2);
			for (int i=0;i<vec_len;i++) printf("%d,",vec2[i]);
			printf("\n");
			for (int64_t i=0;i<sld8-max_len;i++) db3.next();
			for (int i=dump_len;i<vec_len;i++) vec2[i]=db3.next();
		}
	}
	 */
	
	deBruijn dbx(8,12);
	int64_t sl=dbx.get_seq_len();
	printf("seq len %"PRId64"\n",sl);
	
	// We now build lookup tables with 32 segments per sequence
	// The following builds the table for length 5 to max_len sequences
	// The length 10 sequence is ~1.1 billion numbers in length
	// It takes 8-9 seconds to generate
	// The length 12 sequence is ~69 billion numbers in length
	// It takes about 8 minutes to generate
	// The length 14 sequence is ~4.4 trillion numbers in length
	// This should take about ~8 hours to generate
	int max_len=14;
	int min_len=5; //typically start at 5 for the full table
	int vec_len=3*max_len+4;
	int dump_len=2*max_len+4;
	int vec2[vec_len];
	printf("numbers per line is %d\n",vec_len);
	printf("number of lines is %d\n",32*(max_len-4));
	for (int l=min_len;l<=max_len;l++) {
		deBruijn db3(8,l);
		int64_t sld8=db3.get_seq_len()/32;
		for (int i=dump_len;i<vec_len;i++) vec2[i]=7;
		for (int j=0;j<32;j++) {
			for (int i=0;i<dump_len;i++) vec2[i]=0;
			db3.dump_state(vec2);
			for (int i=0;i<vec_len;i++) printf("%d,",vec2[i]);
			printf("\n");
			for (int64_t i=0;i<sld8-max_len;i++) db3.next();
			for (int i=dump_len;i<vec_len;i++) vec2[i]=db3.next();
		}
	}
	
	return 0;
	
}