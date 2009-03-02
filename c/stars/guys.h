#include <err.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _GUYS_H
#define _GUYS_H

typedef struct guy guy;
typedef struct group group;
typedef int g_color;


struct group {
    guy *head;
};


struct guy {
    // x and y coors of position
    int x;
    int y;
    int xlen;
    int ylen;
    g_color color;	// there should be a color type, I just dont know about it yet
    short color_r;
    short color_b;
    short color_g;
    guy *next;
};



extern guy * new_guy(int r, int b, int g);
extern void delete_list_of_guys(guy *head);
extern void set_color(guy*,int,int,int);


#endif
