cc=gcc
ecc=ecc
CFLAGS=-O3
hh=../../../eccws/include/
bb=../../../eccws/libs

all: hs

hs: hs.c
	$(cc) hs.c -o hs $(CFLAGS) -I$(hh) -L$(bb) -leli3lib 

genC: hotspot.esf
	$(ecc) hotspot.esf

clean:
	rm -f *.o hs

