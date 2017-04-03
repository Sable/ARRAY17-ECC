cc=gcc
ecc=ecc
CFLAGS=-O3 -lm
hh=../../../eccws/include/
bb=../../../eccws/libs

all: mg

mg: mg.c
	$(cc) mg.c -o mg $(CFLAGS) -I$(hh) -L$(bb) -leli3lib 

genC: morgan.esf
	$(ecc) morgan.esf

clean:
	rm -f *.o mg

