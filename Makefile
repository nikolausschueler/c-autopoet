include ../../make/progdef

CFLAGS = -Wall -g -I../include -I../misc
PROGS = poet

.SUFFIXES : .c.o

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

poet: poet.o
	$(CC) $(CFLAGS) -o $@ poet.o -lNikBaseC

poet-static: static-lib poet.o
	$(CC) $(CFLAGS) -o $@ poet.o ../misc/libNikBaseC.a

static-lib:
	cd ../misc; make static-lib

install:
	cp poet /usr/local/bin

clean:
	rm -rf $(DELETABLES)

proper: clean
	rm $(PROGS)
