#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/time.h>
#include "drawin.h"

typedef struct food {
	int x, y;
}FOOD, *Food;

#define WIDTH 80
#define HEIGHT 24

int a;
int dir_x, dir_y;
Snake head, tail;
FOOD food;

int set_ticker(int n_msec)
{
	struct itimerval timeset;
	long n_sec, n_usec;

	n_sec = n_msec / 1000;
	n_usec = (n_msec % 1000) * 1000L;

	timeset.it_interval.tv_sec = n_sec;
	timeset.it_interval.tv_usec = n_usec;

	timeset.it_value.tv_sec = n_sec;
	timeset.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL, &timeset, NULL);
}

void Snake_Move()
{
	Snake p, tmp;
	

	for(p = tail; p != head; p = p->prev) {
		p->x = p->prev->x;
		p->y = p->prev->y;
	}
	p->x += dir_x;
	p->y += dir_y;

	move(head->y, head->x);
	if((char)inch()=='*' || (char)inch()=='@') { //eat self and collide with Map
		Game_Over();
	}
	if((char)inch() == 'o') { //eat food
		tmp = (Snake)malloc(sizeof(SNAKE)); //add on next to tail
		tmp->x = tail->x - dir_x;
		tmp->y = tail->y - dir_y;
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;

		drawFood();
	}

	eraseSnake(head);
	drawSnake(head);
}


void Game_Over()
{
	sleep(1);
	clear();
	printw("Restart?(Y/N)");
	set_ticker(0);
	while(1) {
		int ch = getch();
		switch(ch) {
			case 'Y':
			case 'y':
				clear();
				Init();
				set_ticker(500);
				return;
			case 'N':
			case 'n':
				endwin();
				exit(0);
			default:
				break;
		}
	}

}


void key_ctl()
{
	int ch = getch();
	switch(ch) {
		case 'W':
		case 'w':
			if(dir_x == 0)
				break;
			dir_x = 0;
			dir_y = -1;
			break;
		case 'S':
		case 's':
			if(dir_x == 0)
				break;
			dir_x = 0;
			dir_y = 1;
			break;
		case 'A':
		case 'a':
			if(dir_y == 0)
				break;
			dir_y = 0;
			dir_x = -2;
			break;
		case 'D':
		case 'd':
			if(dir_y == 0)
				break;
			dir_y = 0;
			dir_x = 2;
			break;
		case ' ':
			set_ticker(0);
			do {
				ch = getch();
			}while(ch != ' ');
			set_ticker(500);
			break;
		case 'Q':
		case 'q':
			Game_Over();
			break;
		default:break;
	}
}


void Init()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	srand(time(0));

	drawMap();

	dir_x = 2;
	dir_y = 0;
	head = (Snake)malloc(sizeof(SNAKE));
	head->x = rand() % (WIDTH/2-2)*2 + 2;
	head->y = rand() % (HEIGHT/2-2)*2 + 2;
	head->next = (Snake)malloc(sizeof(SNAKE));
	tail = head->next;
	tail->prev = head;
	tail->x = head->x - dir_x;
	tail->y = head->y - dir_y;
	drawSnake(head);

	drawFood();
}

void sig_alrm(int singo)
{
	set_ticker(500);
	Snake_Move();
}
