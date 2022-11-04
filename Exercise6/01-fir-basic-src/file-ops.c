#include <stdlib.h>

#include <file-ops.h>

FILE* openInput(const char* filename) {
    FILE* fp;

    fp = fopen(filename, "r");

    return fp;
}

FILE* openOutput(const char* filename) {
    FILE* fp;

    fp = fopen(filename, "w");

    return fp;
}

void closeFile(FILE* fp) {
    fclose(fp);
}

uint8_t readSample(FILE* fp, bool* success) {
    char buf[16];
    char* ret;
    bool suc = false;
    uint8_t sample = 0;

    ret = fgets(buf, 16, fp);
    if (ret != NULL) {
        suc = true;
    }

    int i = atoi(buf);
    
    if (i < 0) {
        sample = 0;
    } else if (i > 255) {
        sample = 255;
    } else {
        sample = (uint8_t)(i);
    }
    
    if (success != NULL) {
        *success = suc;
    }

    return sample;
}

void writeSample(FILE* fp, uint8_t sample) {
    fprintf(fp, "%d\n", sample);
}