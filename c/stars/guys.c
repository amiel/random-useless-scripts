#include "guys.h"


/*
// this function takes red blue and gree values from 0-255 
// this one WILL ONLY WORK ON 16? bit displays
int rgb(char r, char g, char b){
        return
	      ((int)((double)(r & 0xFF) / 255 * 037) << 11)
	    | ((int)((double)(g & 0xFF) / 255 * 077) << 5)
	    |  (int)((double)(b & 0xFF) / 255 * 037); 
}
*/



// this one is for 24 bit
int rgb(char r, char g, char b){
	return ((r&0xFF) << 16) | ((g&0xFF) << 8) | (b&0xFF);
}





guy * new_guy(int r, int b, int g){
    guy *tmp;

    tmp = emalloc(sizeof(guy));

    // arbitrary values for now
    tmp->x = 20;
    tmp->y = 20;
    tmp->xlen = 0;
    tmp->ylen = 0;
    tmp->color = rgb(r,b,g);
    tmp->color_r = r;
    tmp->color_b = b;
    tmp->color_g = g;

    tmp->next = NULL;
    return tmp;
}



void set_color(guy* tmp, int r, int b, int g){
    tmp->color = rgb(r,g,b);
    tmp->color_r = r;
    tmp->color_b = b;
    tmp->color_g = g;
}
    


void delete_list_of_guys(guy *head){
    guy *tmp;

    while (head != NULL){
	tmp = head->next;
	free(head);
	head = tmp;
    }

    return;
}
