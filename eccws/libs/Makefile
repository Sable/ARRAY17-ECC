#platform=$(shell uname -o)
cc=gcc
hh=../include/
libName=libeli3lib.a

all: $(libName)

$(libName): eli3lib.o
	ar rcs $(libName) eli3lib.o 

eli3lib.o: eli3lib.c
	$(cc) -c eli3lib.c -I$(hh)

clean:
	rm -f *.o $(libName)

