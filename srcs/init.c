#include "wkw.h"

void	init_display(void)
{
	initscr();
	if (has_colors())
	{
		start_color();
		init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(RED, COLOR_RED, COLOR_BLACK);
		init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
		init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
		init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
		clear();
	}
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}
