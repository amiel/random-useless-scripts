CC = gcc
CFLAGS = -D_ERR_LIB



liberr.a: err.o
	ar r liberr.a err.o


err.o: err.h



.PHONY: clean clean-objs again

again: clean liberr.a

clean-objs:
	rm -f err.o

clean: clean-objs
	rm -f liberr.a
