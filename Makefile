all = server client test

CC=gcc-12
CFLAGS=-g -std=c11 -D_GNU_SOURCE -O0
LIBS=

default: $(all)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(all)
