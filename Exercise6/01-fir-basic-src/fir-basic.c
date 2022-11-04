#include <inttypes.h>
#include <stdbool.h>

#include <file-ops.h>

#define K0 37
#define K1 109
#define K2 109
#define K3 37

#define WAV_HEADER_SIZE 44

int16_t __attribute__ ((noinline)) fir(FILE* input, FILE* output) {
    int16_t buffer[4] = {0, 0, 0, 0};
    int16_t s;
    int8_t ws;
    bool readSuccess = false;
    
    s = (int16_t)(readSample(input, &readSuccess));
    s = s - 128;
    
    if (!readSuccess) {
        return 0;
    }

    do {
        // store sample and rotate the oldest data away
        // newest sample goes to buffer[0]
        // previous sample moved to buffer[1]
        // buffer[1] moved to buffer[2]
        // oldest sample buffer[3] is therefore discarded
        buffer[3] = buffer[2];
        buffer[2] = buffer[1];
        buffer[1] = buffer[0];
        buffer[0] = s;

        s = K0*buffer[0];
        s += K1*buffer[1];
        s += K2*buffer[2];
        s += K3*buffer[3];

        ws = (uint8_t)(((s>>8)+128)); 
        writeSample(output, ws);

        s = (int16_t)(readSample(input, &readSuccess));
        s = s - 128;
    } while (readSuccess);

    return s;
}

int copySamples(FILE* input, FILE* output, int n) {
    bool success = false;
    uint8_t s = 0;

    for (int i = 0; i < n; ++i) {
        s = readSample(input, &success);
        if (!success) {
            fprintf(stderr, "failed to copy header bytes!");
            return 1;
        }

        writeSample(output, s);
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "please provide input and output files as first and second argument!\n");
        return 1;
    }
    
    FILE* input = openInput(argv[1]);
    FILE* output = openOutput(argv[2]);

    // copy first 44 bytes as is
    copySamples(input, output, WAV_HEADER_SIZE);

    // then filter the remaining samples
    fir(input, output);
    
    closeFile(input);
    closeFile(output);
}