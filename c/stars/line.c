#include "guys.h"
#include "draw.c"
#include <unistd.h>
#include <time.h>

#define randint(x) ((int)((double)(rand()) / RAND_MAX * (x)))


#define NMOVE  1


int main(){
    guy *g_ptr;
    double slope, b;
    int xdist, ydist,
	rx, ry,
	tmp, i;
    display_info d;

    
    create_window(&d);

    srand(time(NULL));

    
    g_ptr = new_guy(255,255,255);

    rx = 256;
    ry = 256;

    g_ptr->x = randint(MAX_X);
    g_ptr->y = randint(MAX_Y);

    for (i=0;i<32;draw(&d, g_ptr)){
	xdist = rx - g_ptr->x;
	ydist = ry - g_ptr->y;
	if (abs(ydist) > abs(xdist)){
	    slope = (double)ydist / (double)xdist;
	    b = slope * (double)-g_ptr->x + (double)g_ptr->y;
	    printf("%i < %i\tslope:%f\t\tb:%f",ydist,xdist,slope,b);
	    if (g_ptr->x < rx)
		g_ptr->x += NMOVE;
	    else if (g_ptr->x > rx)
		g_ptr->x -= NMOVE;
	    g_ptr->y = slope * (double)g_ptr->x + b;
	    printf("\n");
	} else if (abs(ydist) < abs(xdist)){
	    slope = (double)xdist / (double)ydist;
	    b = slope * (double)-g_ptr->y + (double)g_ptr->x;
	    printf("%i > %i\tslope:%f\t\tb:%f",ydist,xdist,slope,b);
	    if (g_ptr->y < ry)
		g_ptr->y += NMOVE;
	    else if (g_ptr->y > ry)
		g_ptr->y -= NMOVE;
	    g_ptr->x = slope * (double)g_ptr->y + b;
	    printf("\n");
	} else {
	    if (g_ptr->x < rx)
		g_ptr->x += NMOVE;
	    else if (g_ptr->x > rx)
		g_ptr->x -= NMOVE;
	    if (g_ptr->y < ry)
		g_ptr->y += NMOVE;
	    else if (g_ptr->y > ry)
		g_ptr->y -= NMOVE;
	    printf("%i == %i\n",ydist,xdist);
	}
	

	if (abs(xdist) < 15 && abs(ydist) < 15){
	    g_ptr->x = randint(MAX_X);
	    g_ptr->y = randint(MAX_Y);
	    ++i;
	}

    }
    sleep(3);
    printf("done\n");
    delete_list_of_guys(g_ptr);
    return 0;
}


