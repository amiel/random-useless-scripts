#include "guys.h"
#include <unistd.h>
#include <time.h>


#define MAX_X 512
#define MAX_Y 512
#include "draw.c"

#define max(x,y) ((x) > (y) ? (x) : (y))


#define randint(x) ((int)((double)(rand()) / RAND_MAX * (x)))


int main(){
    guy *g_list;
    display_info d;
    int i;
    int tmp;

    srand(time(NULL));

    create_window(&d);

    printf("window created\n");
    g_list = new_guy(0,255,255);
    g_list->next = new_guy(255,0,0);

    /*
    g_list->x = 0;
    g_list->next->x = MAX_X - 2;

    for(i=0;i<=MAX_Y;++i){
	g_list->y=i;
	g_list->next->y=i;
	draw(&d,g_list);
	//usleep(0);
    }


    g_list->y = 0;
    g_list->next->y = MAX_Y - 2;

    for(i=0;i<=MAX_X;++i){
	g_list->x=i;
	g_list->next->x=i;
	draw(&d,g_list);
	//usleep(0);
    }



    g_list->y = MAX_Y / 2;
    g_list->next->x = MAX_X / 2;

    for(i=0;i<=max(MAX_X,MAX_Y);++i){
	g_list->x=i;
	g_list->next->y=i;
	draw(&d,g_list);
	//usleep(9000);
	//usleep(0);
    }

    //sleep(1);



    //printf("RAND_MAX: %i\n",RAND_MAX);
    //fflush(NULL);


    g_list->ylen = 9;
    g_list->next->ylen = 9;

    for(i=0;i<=90100;++i){
	g_list->x = randint(MAX_X);
	g_list->y = randint(MAX_Y);
	g_list->next->x = randint(MAX_X);
	g_list->next->y = randint(MAX_Y);
	g_list->color = rgb(randint(g_list->x),randint(g_list->x),randint(g_list->x));
	g_list->next->color = rgb(randint(g_list->next->x),randint(g_list->next->x),randint(g_list->next->x));
	draw(&d,g_list);
    }


    */
    g_list->ylen = 0;
    g_list->next->ylen = 1;


    g_list->xlen = 1;
    g_list->next->xlen = 0;

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
	sleep(0);
    }

    
    sleep(2);
    
    delete_list_of_guys(g_list);

    return 0;
}
