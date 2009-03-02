

ROOT = /Users/amiel

CC = gcc
CFLAGS = -Wall -I/usr/X11R6/include/X11 -I$(ROOT)/src/c/include
LDFLAGS = -L/usr/X11R6/lib -L$(ROOT)/lib -lX11 -lerr
OBJS = guys.o main.o



.c.o:
	$(CC) $(CFLAGS) -c $<

.o:
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

noarg:
	@echo choose line, scr, main, or clean
.DEFAULT:
	@echo $@ is not an option, you dingus

scr: guys.o scr.o
line: guys.o line.o
line.o: line.c draw.c
scr.o: scr.c draw.c
main: guys.o main.o
main.o: main.c draw.c
guys.o: guys.h


clean:
	rm -f *.o main line scr
