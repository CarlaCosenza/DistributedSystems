#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DES.h"
#include "definitions.h"
#include "keyManipulation.h"

int main(){

	// key_t2 key = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0xD5, 0x94 };
	// const ubyte messagePlain[] = { 0x43, 0x41, 0x4D, 0x49, 0x4E, 0x48, 0x4F, 0x53 };
	// const ubyte messageEncoded[] = { 0x2B, 0xB1, 0x8A, 0xAE, 0xA2, 0xE6, 0x27, 0x8A };
	// char buffer[128];
	// char bufferMessageEncoded[128];
	// int len = sizeof(messagePlain) / sizeof(ubyte);
	
	// String encoded = encrypt(key, messagePlain, len);

	// printBytes(encoded.data, 8, buffer);
	// printf("Encrypted message: %s\n", buffer);

	// printBytes(messageEncoded, 8, bufferMessageEncoded);
	// printf("Expected output: %s\n", bufferMessageEncoded);

	// if(strcmp(buffer, bufferMessageEncoded) == 0){
	// 	printf("DEU CERTO\n");
	// } else {
	// 	printf("TURURU\n");
	// }

	const ubyte messagePlain[] = { 0x43, 0x41, 0x4D, 0x49, 0x4E, 0x48, 0x4F, 0x53 };
	const ubyte messageEncoded[] = { 0x2B, 0xB1, 0x8A, 0xAE, 0xA2, 0xE6, 0x27, 0x8A };
	char buffer[128];
	char bufferMessageEncoded[128];
	printBytes(messageEncoded, 8, bufferMessageEncoded);
	int len = sizeof(messagePlain) / sizeof(ubyte);

	key_t2 key64Bits = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint64_t validKey;
	uint64_t maxValue;
	int keySize = 16;

	getFirstKey(keySize, &maxValue, &validKey, key64Bits);

	while(validKey <= maxValue){
		String encoded = encrypt(key64Bits, messagePlain, len);

		printBytes(encoded.data, 8, buffer);
		printf("Encrypted message: %s\n", buffer);
		printf("Key: ");
		printKey(key64Bits);

		if(strcmp(buffer, bufferMessageEncoded) == 0){
			printf("DEU CERTO\n");
			printf("CHAVE FINAL:  %s\n", buffer);
			printf("CHAVE VALIDA: %14llx\n", validKey);
			return 0;
		} 

		generateNextKey(&validKey, key64Bits);
		// printf("Expected output: %s\n", bufferMessageEncoded);
	}

	printf("TURURU\n");

	return 0;
}