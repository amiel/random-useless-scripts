#include <unistd.h> /* sleep */
#include <Xlib.h>
#include <stdlib.h>
#include <assert.h> /* for assert */
#include <stdio.h>
//#include <keysymdef.h>

#define F_QUIT (1 << 0)





int error(int die,char *s){
	printf("Error: %s\n",s);
	fflush(NULL);
	if (die)
		exit(die);
	return 0;
}



void debug(char *s){
	printf("*** Debug ***  %s\n",s);
	fflush(NULL);
}



/*
#define SNAKE_KEY_UP 'k'
#define SNAKE_KEY_DOWN 'j'
#define SNAKE_KEY_LEFT 'h'
#define SNAKE_KEY_RIGHT 'l'
*/

/*
#define SNAKE_KEY_UP XK_K
#define SNAKE_KEY_DOWN XK_J
#define SNAKE_KEY_LEFT XK_H
#define SNAKE_KEY_RIGHT XK_L
*/




#define SCREEN_MIN_X 0
#define SCREEN_MIN_Y 0
#define SCREEN_MAX_X 800
#define SCREEN_MAX_Y 600



#define MAX_SNAKE_SIZE 16
#define SNAKE_ERR 1
#define SNAKE_OK 0

#define SNAKE_UP 0
#define SNAKE_DOWN 1
#define SNAKE_LEFT 2
#define SNAKE_RIGHT 3






class snake_seg {
	public:
		snake_seg(int sx,int sy);
		~snake_seg();
		int x;
		int y;
//		char c;
		snake_seg *next;
		snake_seg *prev;
};

class snake {
    public:
	snake_seg *head;
	snake_seg *tail;
	snake(int start_size,int x,int y);
	~snake();
	int move(int dir);
	int grow(int amount);
	void draw(Display *,Window,GC,int,int);
    private:
	int size;
};

/************************************************ 
 * new_snake_seg(int x.int y)			*
 * SHOULD ONLY BE CALLED BY new_snake		*
 * args:					*
 * 	x,y:					*
 * 	   starting x,y coordinates		*
 * returns:					*
 * 	a pointer to a snake_seg		*
 ************************************************/ 
snake_seg::snake_seg(int sx,int sy){
	x = sx;
	y = sy;
	next = NULL;
	prev = NULL;
}

/************************************************ 
 * new_snake(int size,int x.int y)		*
 * DONT FORGET TO CALL del_snake		*
 * args:					*
 * 	start_size:				*
 * 	   how many segments to start the	*
 * 	   snake with				*
 * 	x,y:					*
 * 	   starting x,y coordinates		*
 * returns:					*
 * 	a pointer to a snake			*
 ************************************************/ 
snake::snake(int start_size, int x, int y){
	if (start_size < 2 || start_size > MAX_SNAKE_SIZE)
		error(1,"fuck");
	snake_seg *seg;
	
	seg = new snake_seg(x,y);
	if (seg == NULL)
		error(0,"in new snake_seg returned null");

	head = seg;
	// should already be done
	//head->prev = NULL;

	for (size = 1;size < start_size;++size){
		seg->next = new snake_seg(x,y);

		if (seg->next == NULL)
			error(0,"in new snake_seg returned null");
		seg->next->prev = seg;
		seg = seg->next;
	}
	// same here
	//seg->next = NULL;
	tail = seg;
}



int snake::grow(int amount){
	snake_seg *seg;
	if (amount < 1)
		return SNAKE_ERR;
	for (;size < MAX_SNAKE_SIZE && amount > 0;--amount,++size){
		seg = tail;
		seg->next = new snake_seg(seg->x,seg->y);
		if (seg->next == NULL)
			error(0,"in new snake_seg returned null");
		seg->next->prev = seg;
		tail = seg->next;
	}
	return SNAKE_OK;
}



void snake::draw(Display *dpy, Window w, GC gc, int bl, int wh){
    XSetForeground(dpy, gc, bl);
    XDrawPoint(dpy,w,gc,tail->x,tail->y);
    XSetForeground(dpy, gc, wh);
    XDrawPoint(dpy,w,gc,head->x,head->y);
    XFlush(dpy);
}


int snake::move(int dir){
    snake_seg *seg;
    int x;
    int y;

    x = head->x;
    y = head->y;

    seg = tail;
    tail = seg->prev;
    tail->next = NULL;

    seg->prev = NULL;
    seg->next = head;
    seg->next->prev = seg;
    head = seg;

    seg->x = x;
    seg->y = y;


    switch (dir){
	case SNAKE_UP:
	    if (seg->y > SCREEN_MIN_Y)
		--seg->y;
	    else
		seg->y = SCREEN_MAX_Y;
	    break;
	case SNAKE_DOWN:
	    if (seg->y < SCREEN_MAX_Y)
		++seg->y;
	    else
		seg->y = SCREEN_MIN_Y;
	    break;
	case SNAKE_LEFT:
	    if (seg->x > SCREEN_MIN_X)
		--seg->x;
	    else
		seg->x = SCREEN_MAX_X;
	    break;
	case SNAKE_RIGHT:
	    if (seg->x < SCREEN_MAX_X)
		++seg->x;
	    else
		seg->x = SCREEN_MIN_X;
	    break;
	default:
	    return SNAKE_ERR;
	    break;
    }

    return SNAKE_OK;
}







/************************************************ 
* snake::~snake(snake *self):			*
* destructor					*
************************************************/
snake::~snake(){

    debug("in snake::~snake\n");

    snake_seg *seg;
    while(head){
	seg = head->next;
	free(head);
	head = seg;
    }
}



int main(){
    char flags;
    int dir = SNAKE_DOWN;


    Display *dpy = XOpenDisplay(NULL);
    assert(dpy);


    int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
    int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));




    
    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, blackColor, blackColor);


    XSelectInput(dpy, w, StructureNotifyMask);
    XMapWindow(dpy, w);
    GC gc = XCreateGC(dpy, w, 0, NULL);

    for(;;) {
	XEvent e;
	XNextEvent(dpy, &e);
	if (e.type == MapNotify)
	    break;
    }


    /*int keyret;
    keyret = XGrabKey(dpy, w, AnyKey, AnyModifier, 0, GrabModeAsync, GrabModeAsync);

    switch (keyret){
	case BadValue:
	    error(1,"keygrab badvalue");
	    break;
	case BadWindow:
	    error(1,"keygrab badwindow");
	    break;
	default:
	    debug("good grab");
	    printf("## DEBUG ## %i is keyret\n", keyret);
	    break;
    }
    */
    
    snake me(8,5,5);

    XSelectInput(dpy, w, StructureNotifyMask);
    XEvent e;
    for (;;){
	usleep(20200);
	me.draw(dpy,w,gc,blackColor,whiteColor);
	XNextEvent(dpy, &e);
	if (e.type == XKeyEvent){
	    switch (XKeycodeToKeysym(dpy, e.xkey.keycode, 0)){
		case XK_K://SNAKE_KEY_UP:
		    if (dir != SNAKE_DOWN){
			me.move(SNAKE_UP);
			dir = SNAKE_UP;
		    }
		    break;
		case XK_J://SNAKE_KEY_DOWN:
		    if (dir != SNAKE_UP){
			me.move(SNAKE_DOWN);
			dir = SNAKE_DOWN;
		    }
		    break;
		case XK_H://SNAKE_KEY_LEFT:
		    if (dir != SNAKE_RIGHT){
			me.move(SNAKE_LEFT);
			dir = SNAKE_LEFT;
		    }
		    break; 
		case XK_L://SNAKE_KEY_RIGHT:
		    if (dir != SNAKE_LEFT){
			me.move(SNAKE_RIGHT);
			dir = SNAKE_RIGHT;
		    }
		    break;
		case XK_G:
		    me.grow(1);
		    break;
		case XK_Q:
		    flags|=F_QUIT;
		    break;
		default:
		    me.move(dir);
		    break;
	    }
	} else {
	    me.move(dir);
	}
	if (flags & F_QUIT)
	    break;
    }

    //XUngrabKey(dpy, AnyKey, AnyModifier, w);

    return 0;
}
