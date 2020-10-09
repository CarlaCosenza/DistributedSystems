#include <stdio.h>

#include "keyManipulation.h"

void generate64BitKey(uint64_t validKey, key_t2 key){
	int i, j;
	for(i = 0 ; i < 8 ; i++){
		unsigned char bits7 = validKey%128;
		unsigned char bitParityAnalyzer = bits7;
		int zeroCounter = 0;
		for(j = 0 ; j < 7 ; j++){
			if(bitParityAnalyzer%2 == 0) zeroCounter++;
			bitParityAnalyzer = bitParityAnalyzer/2;
		}

		// Generate 8 bit unsigned char with parity
		bits7 = bits7 << 1;
		bits7 = bits7 + (zeroCounter%2);
		key[7-i] = bits7;

		validKey = validKey/128;
	}

	return;
}

void getFirstKey(int keySize, uint64_t* maxValue, uint64_t* validKey, key_t2 key){
	int i;
	*maxValue = 1;
	for(i = 0 ; i < keySize ; i++){
		*maxValue = *maxValue << 1;
	}
	*maxValue = *maxValue - 1;
	*validKey = 0;

	generate64BitKey(*validKey, key);

	return; 
}

void generateNextKey(uint64_t* validKey, key_t2 key){
	*validKey = *validKey + 1;

	generate64BitKey(*validKey, key);

	return;
}

void printKey(key_t2 key){
	int i;
	for(i = 0 ; i < 8 ; i++){
		printf("%x ", key[i] & 0xff);
	}
	printf("\n");

	return;
}