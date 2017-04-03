cc=gcc
ecc=ecc
CFLAGS=-O3
hh=../../../eccws/include/
bb=../../../eccws/libs

all: km 

km: km.c
	$(cc) km.c -o km $(CFLAGS) -I$(hh) -L$(bb) -leli3lib -lm

genC: kmeans.esf
	$(ecc) kmeans.esf

clean:
	rm -f *.o km

