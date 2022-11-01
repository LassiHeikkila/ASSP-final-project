# ASSP Final Project - Task 1 - Matrix multiplication in C
## Build and run
To build, simply run:
```console
make
```
This will produce and executable called `matrixmultiply`.  
The program reads two matrices from stdin, so you can enter them by typing or piping a text file to stdin.  
The program expects matrices to be given as floating point numbers in matlab matrix format, so e.g. this matrix:  
```
1 2
3 4
```
should be entered as:  
```
[ 1.0 2.0; 3.0 4.0 ]
```

By default, intermediate calculations are done using half-precision floating point numbers.

Example:
```console
$ ./matrixmultiply
Enter matrix A:
[1.0 0.0; 0.0 1.0]
Enter matrix B:
[2.0 0.0; 0.0 3.0]
result:
[ 2.000000 0.000000; 0.000000 3.000000 ]
```

### Fixed point mode
Fixed point mode can be enabled using flag `-f`.

Fixed point mode uses scaling factor `1<<8` with 16 bit signed numbers, 
so the minimum supported value is `-128.0` and the maximum supported value is `127.996094`.

Row and column products in matrix multiplication are subject to these limits.

## Running tests
Simply run:
```console
make test
```

## Re-building after making changes
The [Makefile](Makefile) is not very sophisticated, so it's a good idea to run `make clean` and then re-build everything to make sure all object files include the latest changes.