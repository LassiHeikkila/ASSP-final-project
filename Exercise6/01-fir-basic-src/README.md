# Basic FIR filter implementation in C
This directory contains a basic FIR filter implementation in C which can be compiled and run on a normal Linux PC.

## Compiling
```console
gcc -o fir-basic file-ops.c fir-basic.c -I.
```

## Running
First argument is the input file, second argument is the output file.
```console
$ cp ../data/input.in input.in
$ ./fir-basic ../data/input.in output.out
```

[Output](output.out) is very similar to the [reference output](../data/reference.out), so the filter is working:
```console
$ typeout ./output.out
Sum: 2084451

$ typeout ../data/reference.out 
Sum: 2085077
```

Listening to the [`output.out` waveform](output.wav) also confirms that the filter works, as the annoying high pitched noise is removed.
A utility program for converting `INPUT.in` and `output.out` to proper wav format that can be played with audio player can be found [here](../util/dec2bin/).