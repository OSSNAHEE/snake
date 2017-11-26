#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct snake {
	int x, y;
	struct snake *next, *prev;
}SNAKE, *Snake;

typedef struct food {
	int x, y;
}FOOD, *Food;

#define WIDTH 80
#define HEIGHT 24

Snake head, tail;
FOOD food;


void drawMap()
{
	for(int x=0; x<WIDTH; x+=2) {
		for(int y=0; y<HEIGHT; y++) {
			if(x==0 || y==0 || x==WIDTH-2 || y==HEIGHT-1){
				move(y,x);
				addch('@');
			}
		}
	} //need obstacle
	refresh();
}

void drawSnake(Snake p)
{
	start_color();			/* Start color*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
	
	for(; p!=tail; p=p->next) {
		move(p->y,p->x);
		if(p==head)
		{
			attron(COLOR_PAIR(1));
			addch('*');
			attroff(COLOR_PAIR(1));
		}
		else
		{
			attron(COLOR_PAIR(2));
			addch('*');
			attroff(COLOR_PAIR(2));
		}
	}
	refresh();
}

void eraseSnake(Snake p)
{
	for(; p!=NULL; p=p->next) {
		move(p->y,p->x);
		addch(' ');
	}
	refresh();
}

void drawFood()
{
	do {
		food.x = rand() % (WIDTH/2-2)*2 + 2;
		food.y = rand() % (HEIGHT/2-2)*2 + 2;
		move(food.y, food.x);
	}while(((char)inch()) == '*');
	move(food.y, food.x);
	addch('o');
	refresh();
}
