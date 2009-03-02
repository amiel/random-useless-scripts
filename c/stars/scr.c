#include "guys.h"
#include <unistd.h>
#include <time.h>
#include <math.h>


#define MAX_X 1024
#define MAX_Y 512

#include "draw.c"




#define NBALLS  64
#define NMOVE   1
#define NSWITCH 64


//#define max(x,y) ((x) > (y) ? (x) : (y))
//#define min(x,y) ((x) < (y) ? (x) : (y))


#define randint(x) ((int)((double)(rand()) / RAND_MAX * (x)))


int main(){
    group g_list;
    guy *g_ptr;
    display_info d;
    int //tmp,
	rx, ry,
    	//max, min,
    	xdist, ydist;
    unsigned long i;
    double slope, b;
    //g_color color;

    srand(time(NULL));

    create_window(&d);

    g_list.head = new_guy(randint(255),randint(255),randint(255));
    g_ptr = g_list.head;
    for (i=0;i<NBALLS;++i){
	//printf("creating guy %i...",i);
	g_ptr->next = new_guy(randint(255),randint(255),randint(255));
	g_ptr = g_ptr->next;
	//printf("%p\n",g_ptr);
	g_ptr->x = randint(MAX_X);
	g_ptr->y = randint(MAX_Y);
	//tmp = randint(2);
	//g_ptr->xlen = g_ptr->ylen = tmp;
        g_ptr->xlen = g_ptr->ylen = randint(2);
    }


    /*rx = randint(MAX_X);
    ry = randint(MAX_Y);
    printf("rx:%i/%i\try:%i/%i\n",rx,MAX_X,ry,MAX_Y);*/
    for(i=0;1;++i){
		
	if (i%NSWITCH==0){
	    rx = randint(MAX_X);
	    ry = randint(MAX_Y);
#           if DEBUG
                printf("i:%i\trx:%i/%i\try:%i/%i\n",i,rx,MAX_X,ry,MAX_Y);
#           endif
	}

	for(g_ptr = g_list.head; g_ptr != NULL; g_ptr = g_ptr->next){
	    //color = g_ptr->color;
            // setting color directly saves color_[rbg]
	    g_ptr->color = 0; // erase old dot
	    draw(&d,g_list.head);


	    xdist = rx - g_ptr->x;
	    ydist = ry - g_ptr->y;
	    if (abs(ydist) > abs(xdist)){
                // why abs?, I dunno, to be weird, it looks cool
		slope = abs((double)ydist / (double)xdist);
		b = slope * (double)-g_ptr->x + (double)g_ptr->y;
		if (g_ptr->x < rx)
		    g_ptr->x += NMOVE;
		else if (g_ptr->x > rx)
		    g_ptr->x -= NMOVE;
		g_ptr->y = slope * (double)g_ptr->x + b;
	    } else if (abs(ydist) < abs(xdist)){
                // why abs?, I dunno, to be weird
		slope = abs((double)xdist / (double)ydist);
		b = slope * (double)-g_ptr->y + (double)g_ptr->x;
		if (g_ptr->y < ry)
		    g_ptr->y += NMOVE;
		else if (g_ptr->y > ry)
		    g_ptr->y -= NMOVE;
		g_ptr->x = slope * (double)g_ptr->y + b;
	    } else {
		if (g_ptr->x < rx)
		    g_ptr->x += NMOVE;
		else if (g_ptr->x > rx)
		    g_ptr->x -= NMOVE;
		if (g_ptr->y < ry)
		    g_ptr->y += NMOVE;
		else if (g_ptr->y > ry)
		    g_ptr->y -= NMOVE;
	    }
	    


//            g_ptr->x += 5;

	    if (
                    ( abs(xdist) < 15 && abs(ydist) < 15 )
                 || ( g_ptr->x > MAX_X || g_ptr->y > MAX_Y )
                 || ( g_ptr->x < 0 || g_ptr->y < 0 )
               ) {
		g_ptr->x = randint(MAX_X);
		g_ptr->y = randint(MAX_Y);
	    }

            // this gets crazy
	    set_color(g_ptr,g_ptr->color_r+1,g_ptr->color_b+1,g_ptr->color_g+1);
	    draw(&d,g_list.head);
	}
    }
/*

    g_list->ylen = 0;
    g_list->next->ylen = 0;


    g_list->xlen = 5;
    g_list->next->xlen = 5;

    for(i=0;i<=990100;++i){
	g_list->x = randint(MAX_X);
	g_list->y = randint(MAX_Y);
	g_list->next->x = randint(MAX_X);
	g_list->next->y = randint(MAX_Y);
	tmp = ((g_list->x % (255)) + (g_list->y % (255)));
	g_list->color = rgb(randint(tmp),randint(tmp),randint(tmp));
	tmp = ((g_list->next->x + g_list->next->y) % 512) / 2;
	g_list->next->color = rgb(randint(tmp),randint(tmp),randint(tmp));
	draw(&d,g_list);
    }

    
    sleep(2);
    
    */
    sleep(1);
    delete_list_of_guys(g_list.head);

    return 0;
}
