#include <X11/Xlib.h>
#include <stdio.h>
#include <assert.h>
#include "guys.h"

#ifndef MAX_X
#   define MAX_X 512
#endif

#ifndef MAX_Y
#   define MAX_Y 512
#endif


//#define ROOT_SCREEN



typedef struct display_info display_info;

struct display_info {
    Display *dpy;
    Window w;
    GC gc;
};


void create_window(display_info *info){
#   ifndef ROOT_SCREEN
	XEvent e;
#   endif
    int blackColor;
    int whiteColor;

    /*
    printf("opening display on mud.lakes.cs.wwu.edu:0\n");
    fflush(NULL);
    info->dpy = XOpenDisplay("mud.lakes.cs.wwu.edu:0");
    printf("XOpen display returned %p\n",info->dpy);
    fflush(NULL);
    assert(info->dpy);
    printf("passed assert\n");
    fflush(NULL);
    */
    info->dpy = XOpenDisplay(NULL);
    assert(info->dpy);

    blackColor = BlackPixel(info->dpy, DefaultScreen(info->dpy));
    whiteColor = WhitePixel(info->dpy, DefaultScreen(info->dpy));
 
      
#   ifndef ROOT_SCREEN
	info->w = XCreateSimpleWindow(info->dpy, DefaultRootWindow(info->dpy), 0, 0, MAX_X, MAX_Y, 10, whiteColor, blackColor);
#   else
	info->w = DefaultRootWindow(info->dpy);
#   endif

    XSelectInput(info->dpy, info->w, StructureNotifyMask);
    XMapWindow(info->dpy, info->w);
    info->gc = XCreateGC(info->dpy, info->w, 0, NULL);

#   ifdef ROOT_SCREEN
	return;
#   else
	for(;;) {
	    XNextEvent(info->dpy, &e);
	    if (e.type == MapNotify)
	    break;
	}
	return;
#   endif
}


void draw(display_info *d, guy *me){
    int x=0,y=0;
    
    for(  ; me != NULL; me = me->next){
	XSetForeground(d->dpy, d->gc, me->color);
	for (x=-me->xlen;x<=me->xlen;++x)
	    for (y=-me->ylen;y<=me->ylen;++y)
		XDrawPoint(d->dpy,d->w,d->gc,me->x+x,me->y+y);

	XFlush(d->dpy);
    }
}
