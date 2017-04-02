cc=gcc
ecc=ecc
CFLAGS=-O3
hh=../../../eccws/include/
bb=../../../eccws/libs

all: rp

rp: rp.c
	$(cc) rp.c -o rp $(CFLAGS) -I$(hh) -L$(bb) -leli3lib 

genC: rprime.esf
	$(ecc) rprime.esf

clean:
	rm -f *.o rp

