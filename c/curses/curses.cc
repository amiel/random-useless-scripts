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
	fflush(NULL);
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
		error(5,"in new snake_seg returned null");

	head = seg;
	// should already be done
	//head->prev = NULL;

	for (size = 1;size < start_size;++size){
		seg->next = new snake_seg(x,y);

		if (seg->next == NULL)
			error(5,"in new snake_seg returned null");
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
			error(5,"in new snake_seg returned null");
		seg->next->prev = seg;
		tail = seg->next;
	}
	return SNAKE_OK;
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

	printf("### debug ### in snake::~snake\n");
	fflush(NULL);

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
	initscr(); cbreak(); noecho();
	
	nonl();

	nodelay(stdscr, TRUE);
	//halfdelay(1);
	//leaveok(stdscr, TRUE);
	//intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);


	snake me(8,5,5);
	
	for (;;){
		usleep(20200);
		mvaddch(me.tail->y,me.tail->x,' ');
		move(0,0);
		refresh();
		switch (getch()){
			case ERR:
				me.move(dir);
				break;
			case KEY_UP:
				if (dir != SNAKE_DOWN)
					dir = SNAKE_UP;
				me.move(dir);
				break;
			case KEY_DOWN:
				if (dir != SNAKE_UP)
					dir = SNAKE_DOWN;
				me.move(dir);
				break;
			case KEY_LEFT:
				if (dir != SNAKE_RIGHT)
					dir = SNAKE_LEFT;
				me.move(dir);
				break; 
			case KEY_RIGHT:
				if (dir != SNAKE_LEFT)
					dir = SNAKE_RIGHT;
				me.move(dir);
				break;
			case 'g':
				me.grow(1);
				break;
			case 'q':
				flags|=F_QUIT;break;
			default:
				/* nothing */
				break;
		}
		mvaddch(me.head->y,me.head->x,'#');
		if (flags & F_QUIT)
			break;
	}

	endwin();

	return 0;
}
