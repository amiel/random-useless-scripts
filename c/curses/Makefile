CFLAGS=-g -Wall
LIBS=-lncurses

XCFLAGS=${CFLAGS} -I/usr/X11R6/include/X11
XLIBS=-L/usr/X11R6/lib -lX11

#OBJS=curses.c
#PROG=curse


#${PROG}:${OBJS}
#	${CC} ${CFLAGS} $? -o $@ ${LIBS}


default: xwin


all: cc cpp


help:
	@echo -e "please use\nmake cc\nor\nmake cpp"


xwin: xwin.cc
	g++ ${XCFLAGS} -o main_cpp $? ${XLIBS}

cc: curses.c
	gcc $(CFLAGS) -o main_c $? ${LIBS}



cpp: curses.cc
	g++ $(CFLAGS) -o main_cpp $? ${LIBS}



clean:
	rm main_cpp main_c
