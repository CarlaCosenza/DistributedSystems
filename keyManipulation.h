#ifndef KEY_MANIPULATION
#define KEY_MANIPULATION

#include <stdint.h>

#include "definitions.h"

void getFirstKey(int keySize, uint64_t* maxValue, uint64_t* validKey, key_t2 key);
void generate64BitKey(uint64_t validKey, key_t2 key);
void generateNextKey(uint64_t* validKey, key_t2 key);
void printKey(key_t2 key, FILE* fp);

#endif