#include <unistd.h>
#include <curses.h>
#include <stdlib.h>

#define F_QUIT (1 << 0)




int error(int die,char *s){
	endwin();
	printf("Error: %s\n",s);
	fflush(NULL);
	if (die)
		exit(die);
	return 0;
}


#define SCREEN_MIN_X 0
#define SCREEN_MIN_Y 0
#define SCREEN_MAX_X 80
#define SCREEN_MAX_Y 20


#define MAX_SNAKE_SIZE 50
#define SNAKE_ERR 1
#define SNAKE_OK 0

#define SNAKE_UP 0
#define SNAKE_DOWN 1
#define SNAKE_LEFT 2
#define SNAKE_RIGHT 3

typedef struct snake snake;
typedef struct snake_seg snake_seg;

struct snake_seg {
	int x;
	int y;
//	char c;
	snake_seg *next;
	snake_seg *prev;
};

struct snake {
	snake_seg *head;
	snake_seg *tail;
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
snake_seg *new_snake_seg(int x,int y){
	snake_seg *self;

	self = malloc(sizeof(snake_seg));
	if (self == NULL)
		error(5,"in new_snake_seg malloc returned null\n");

	self->x = x;
	self->y = y;
	self->next = NULL;
	self->prev = NULL;
	return self;
}

/************************************************ 
 * new_snake(int size,int x.int y)		*
 * DONT FORGET TO CALL del_snake		*
 * args:					*
 * 	size:					*
 * 	   how many segments to start the	*
 * 	   snake with				*
 * 	x,y:					*
 * 	   starting x,y coordinates		*
 * returns:					*
 * 	a pointer to a snake			*
 ************************************************/ 
snake *new_snake(int size, int x, int y){
	snake *self;
	snake_seg *seg;
	if (size < 2 || size > MAX_SNAKE_SIZE)
		return NULL;
	self = malloc(sizeof(snake));
	if (self == NULL)
		error(5,"in new_snake malloc returned null\n");

	// start with 1 and increment in the for loop below
	seg = new_snake_seg(x,y);
	self->head = seg;
	// should already be done
	//self->head->prev = NULL;
	for (self->size = 1;self->size < size;++self->size){
		seg->next = new_snake_seg(x,y);
		seg->next->prev = seg;
		seg = seg->next;
	}


	// same here
	//seg->next = NULL;
	self->tail = seg;
	return self;
}








int snake_grow(snake *self,int amount){
	snake_seg *seg;
	if (amount < 1)
		return SNAKE_ERR;
	for (;self->size < MAX_SNAKE_SIZE && amount > 0;--amount,++self->size){
		seg = self->tail;
		seg->next = new_snake_seg(seg->x,seg->y);
		if (seg->next == NULL)
			error(5,"in new snake_seg returned null");
		seg->next->prev = seg;
		self->tail = seg->next;
	}
	return SNAKE_OK;
}



int snake_move(snake *self,int dir){
    snake_seg *seg;
    int x;
    int y;

    if (self == NULL)
	return SNAKE_ERR;

    x = self->head->x;
    y = self->head->y;

    seg = self->tail;
    self->tail = seg->prev;
    self->tail->next = NULL;

    seg->prev = NULL;
    seg->next = self->head;
    seg->next->prev = seg;
    self->head = seg;

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
 * del_snake(snake *self):			*
 * args:					*
 * 	self:					*
 * 	   the snake to delete			*
 * returns:					*
 * 	nothing					*
 ************************************************/
void del_snake(snake *self){
	snake_seg *seg;
	while(self->head){
		seg = self->head->next;
		free(self->head);
		self->head = seg;
	}
	free(self);
	// we dont really need this because its the end of the scope
	//self = NULL;
}



int main(){
	int dir = SNAKE_DOWN;
	char flags;
	snake *me;
	initscr(); cbreak(); noecho();
	
	nonl();

	nodelay(stdscr, TRUE);
	//leaveok(stdscr, TRUE);
	//intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	me = new_snake(8,5,5);


	for (;;){
		usleep(20200);
		mvaddch(me->tail->y,me->tail->x,' ');
		move(0,0);
		refresh();
		switch (getch()){
			case ERR:
				snake_move(me,dir);
				break;
			case KEY_UP:
				if (dir != SNAKE_DOWN)
					dir = SNAKE_UP;
				snake_move(me,dir);
				break;
			case KEY_DOWN:
				if (dir != SNAKE_UP)
					dir = SNAKE_DOWN;
				snake_move(me,dir);
				break;
			case KEY_LEFT:
				if (dir != SNAKE_RIGHT)
					dir = SNAKE_LEFT;
				snake_move(me,dir);
				break; 
			case KEY_RIGHT:
				if (dir != SNAKE_LEFT)
					dir = SNAKE_RIGHT;
				snake_move(me,dir);
				break;
			case 'g':
				snake_grow(me,1);
				break;
			case 'q':
				flags|=F_QUIT;break;
			default:
				/* nothing */
				break;
		}
		mvaddch(me->head->y,me->head->x,'#');
		if (flags & F_QUIT)
			break;
	}


	del_snake(me);
	me = NULL;
	endwin();

	return 0;
}
