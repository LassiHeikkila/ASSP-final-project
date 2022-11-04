#include <inttypes.h>
#include <stdbool.h>

#define K0 37
#define K1 109
#define K2 109
#define K3 37

#define WAV_HEADER_SIZE 44

int16_t __attribute__ ((noinline)) fir() {
    int data, status, done = 0;
    int16_t buffer[4] = {0, 0, 0, 0};
    int16_t s;
    int8_t ws;
    bool readSuccess = false;
    
    _TCE_FIFO_U8_STREAM_IN(0, data, status);
    s = (int16_t)data;
    s = s - 128;
    
    if (status == 0) {
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

        // reset accumulator to 0
        _TCE_SET_ACC(0);

        // call MAC instruction, we only need the last accumulator value so its ok to overwrite s with each call
        _TCE_MAC32(K0, buffer[0], s);
        _TCE_MAC32(K1, buffer[1], s);
        _TCE_MAC32(K2, buffer[2], s);
        _TCE_MAC32(K3, buffer[3], s);

        ws = (uint8_t)(((s>>8)+128));
        _TCE_FIFO_U8_STREAM_OUT(ws);

        _TCE_FIFO_U8_STREAM_IN(0, data, status);
        s = (int16_t)data;
        s = s - 128;
        done = (status == 0);
    } while (!done);

    return s;
}

int copySamples(int n) {
    int i, data, status = 0;
    uint8_t s = 0;

    for (i = 0; i < n; ++i) {
        _TCE_FIFO_U8_STREAM_IN(0, data, status);
        _TCE_FIFO_U8_STREAM_OUT(data);
    }
    return 0;
}

int main(int argc, char** argv) {    
    // copy first 44 bytes as is
    copySamples(WAV_HEADER_SIZE);

    // then filter the remaining samples
    fir();
}