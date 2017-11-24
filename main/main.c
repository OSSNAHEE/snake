/*
************************************
* wsad控制上下左右，q退出，空格暂停
* 编译命令 gcc snake.c -lcurses
* 可能需要下载ncurses库，具体方法请百度
* 发现bug请在贴吧@微笑一日
*************************************
*/
/*
*************************************
*how to play: w:up, s:down, a:left, d:right, q:quit, space:pause
*compile : gcc snake.c -lcurses
*you may need curses library,please google it
*if you find bugs,mail me at weixiaoyiri@gmali.com
*************************************
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/time.h>
#include "funin.h"

int main()
{
	char ch;
	
	clear();
	Init();
	signal(SIGALRM, sig_alrm);
	set_ticker(100);

	while(1) {
	key_ctl();
	}
	endwin();
	return 0;
}
