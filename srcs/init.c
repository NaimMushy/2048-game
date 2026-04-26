#include "wkw.h"

void	init_display(void)
{
	initscr();
	if (has_colors())
	{
		start_color();
		// init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
		// init_pair(RED, COLOR_RED, COLOR_BLACK);
		// init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
		// init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		// init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
		// init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
		// init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
		init_color(14, RGB_TO_CURSES(153), RGB_TO_CURSES(33), RGB_TO_CURSES(17));
		init_pair(RRED, 14, COLOR_BLACK);
		init_color(15, RGB_TO_CURSES(191), RGB_TO_CURSES(85), RGB_TO_CURSES(13));
		init_pair(ORANGE, 15, COLOR_BLACK);
		init_color(16, RGB_TO_CURSES(212), RGB_TO_CURSES(169), RGB_TO_CURSES(15));
		init_pair(RYELLOW, 16, COLOR_BLACK);
		init_color(17, RGB_TO_CURSES(107), RGB_TO_CURSES(173), RGB_TO_CURSES(68));
		init_pair(RGREEN, 17, COLOR_BLACK);
		init_color(18, RGB_TO_CURSES(68), RGB_TO_CURSES(173), RGB_TO_CURSES(166));
		init_pair(RBLUE, 18, COLOR_BLACK);
		init_color(19, RGB_TO_CURSES(99), RGB_TO_CURSES(64), RGB_TO_CURSES(130));
		init_pair(PURPLE, 19, COLOR_BLACK);
		clear();
	}
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}
