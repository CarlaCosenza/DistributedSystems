#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "DES.h"
#include "definitions.h"
#include "keyManipulation.h"

int main(){

	int rep;
	for(rep = 0 ; rep < 4 ; rep++){

		// Start ime variables
		struct timeval startTime;
		gettimeofday(&startTime, NULL);

		// Message variable
		const ubyte messagePlain[] = { 0x46, 0x45, 0x52, 0x52, 0x4F, 0x56, 0x49, 0x41 };
		const ubyte messageEncoded[] = { 0xAC, 0xCC, 0xCA, 0xAB, 0x8E, 0x11, 0xF2, 0xB7 };
		// const ubyte messageEncoded[] = { 0xF9, 0x19, 0xBF, 0x01, 0xFD, 0x14, 0xA3, 0xE2 };
		char buffer[128];
		char bufferMessageEncoded[128];
		printBytes(messageEncoded, 8, bufferMessageEncoded);
		int len = sizeof(messagePlain) / sizeof(ubyte);
		int foundAnswer = 0;

		// Key variables
		key_t2 key64Bits = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		uint64_t validKey;
		uint64_t maxValue;
		int keySize = 32;

		getFirstKey(keySize, &maxValue, &validKey, key64Bits);

		// Test all possible keys
		while(validKey <= maxValue){
			String encoded = encrypt(key64Bits, messagePlain, len);

			printBytes(encoded.data, 8, buffer);

			if(strcmp(buffer, bufferMessageEncoded) == 0){
				foundAnswer = 1;
				break;
			} 

			generateNextKey(&validKey, key64Bits);
		}

		// End time variable
		struct timeval endTime;
		gettimeofday(&endTime, NULL);

		// Calculate execution time
		long seconds = (endTime.tv_sec - startTime.tv_sec);
		long miliseconds = ((seconds * 1000000) + endTime.tv_usec) - (startTime.tv_usec);

		// Creating output file
		FILE *fp;
		fp = fopen("output.txt", "a");

		// Write to output file
		if(foundAnswer == 0){
			fprintf(fp, "Did not find key.\n");
		} else {
			fprintf(fp, "Found key of 64 bits: ");
			printKey(key64Bits, fp);
			fprintf(fp, "Valid 56 bit key: %014llx\n", validKey);
			fprintf(fp, "Execution time: %ld.%ld seconds \n \n", seconds, miliseconds);
		}

		// Close output file
		fclose(fp);
	}

	return 0;
}