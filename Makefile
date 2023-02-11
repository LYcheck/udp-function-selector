all = sockserver sockclient test

CC=gcc
CFLAGS=-g -std=c11
LIBS=

default: $(all)

curl curlmulti: LIBS+=-lcurl

sockclient: CFLAGS+= -D_GNU_SOURCE

fileio: fileio.c input.dat
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
input.dat:
	@echo "1 2\n3 4 5 6" > $@

mqueue: LIBS+=-lrt

mmap: mmap.c example.txt
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
example.txt:
	@echo "This is sample text." > $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(all) example.txt input.dat
