#ifndef DES 
#define DES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"

typedef struct {
    ubyte *data;
    int len;
} String;

String encrypt(const key_t2 key, const ubyte *message, int len);
void printBytes(const ubyte *ptr, int len, char *out);

#endif