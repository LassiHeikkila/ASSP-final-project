#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

FILE* openInput(const char* filename);
FILE* openOutput(const char* filename);

void closeFile(FILE* f);

uint8_t readSample(FILE* f, bool* success);
void writeSample(FILE* f, uint8_t sample);

#endif