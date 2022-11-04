# dec2bin
This simple program converts a file containing lines with one decimal number between 0 and 255 to a file containing plain bytes corresponding to each number.

For example [input.in](../../data/input.in) was converted to [input.wav](../data/../../data/input.wav) using this program.

Input is read from `stdin` and output is written to `stdout`.

## Running
```console
./dec2bin > output.wav < OUTPUT.out
```

## Building
From this (`util/dec2bin`) directory, execute:
```console
go build .
```
Requires having Go toolchain installed.