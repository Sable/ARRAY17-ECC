cc=gcc
ecc=ecc
CFLAGS=-O3 -lm
hh=../../../eccws/include/
bb=../../../eccws/libs

all: bs

bs: BlackScholes.c
	$(cc) BlackScholes.c -o bs $(CFLAGS) -leli3lib -I$(hh) -L$(bb)

genC: black.esf
	$(ecc) black.esf

clean:
	rm -f *.o BlkSchls

