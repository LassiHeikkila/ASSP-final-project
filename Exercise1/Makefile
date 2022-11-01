IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)
DEBUG_CFLAGS=$(CFLAGS) -g

ODIR=src
LDIR=lib

LIBS=-lm

_DEPS = fixed-point.h io.h matrix-multiplication.h float16.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = matrix-multiplication.o float16.o fixed-point.o serde.o
_MAINOBJ = main.o
_TESTOBJ = test.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
MAINOBJ = $(patsubst %,$(ODIR)/%,$(_MAINOBJ))
TESTOBJ = $(patsubst %,$(ODIR)/test/%,$(_TESTOBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(DEBUG_CFLAGS)

matrixmultiply: $(MAINOBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

dbg: $(MAINOBJ) $(OBJ)
	$(CC) -o matrixmultiply-$@ $^ $(DEBUG_CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/test/*.o *~ core $(INCDIR)/*~ matrixmultiply*

.PHONY: test

test: $(TESTOBJ) $(OBJ)
	$(CC) -o matrixmultiply-$@ $^ $(DEBUG_CFLAGS) $(LIBS) && ./matrixmultiply-$@
