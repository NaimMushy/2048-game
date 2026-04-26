#include "wkw.h"

void	init_display(t_display *display)
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
		init_color(RED1, RGB_TO_CURSES(153), RGB_TO_CURSES(33), RGB_TO_CURSES(17));
		init_pair(NB_COLORS + RED1, RED1, COLOR_BLACK);
		init_color(ORANGE, RGB_TO_CURSES(191), RGB_TO_CURSES(85), RGB_TO_CURSES(13));
		init_pair(NB_COLORS + ORANGE, ORANGE, COLOR_BLACK);
		init_color(YELLOW1, RGB_TO_CURSES(212), RGB_TO_CURSES(169), RGB_TO_CURSES(15));
		init_pair(NB_COLORS + YELLOW1, YELLOW1, COLOR_BLACK);
		init_color(GREEN1, RGB_TO_CURSES(107), RGB_TO_CURSES(173), RGB_TO_CURSES(68));
		init_pair(NB_COLORS + GREEN1, GREEN1, COLOR_BLACK);
		init_color(BLUE1, RGB_TO_CURSES(68), RGB_TO_CURSES(173), RGB_TO_CURSES(166));
		init_pair(NB_COLORS + BLUE1, BLUE1, COLOR_BLACK);
		init_color(PURPLE1, RGB_TO_CURSES(99), RGB_TO_CURSES(64), RGB_TO_CURSES(130));
		init_pair(NB_COLORS + PURPLE1, PURPLE1, COLOR_BLACK);
		init_color(RED2, RGB_TO_CURSES(245), RGB_TO_CURSES(53), RGB_TO_CURSES(39));
		init_pair(NB_COLORS + RED2, RED2, COLOR_BLACK);
		init_color(GREEN2, RGB_TO_CURSES(43), RGB_TO_CURSES(128), RGB_TO_CURSES(71));
		init_pair(NB_COLORS + GREEN2, GREEN2, COLOR_BLACK);
		init_color(BLUE2, RGB_TO_CURSES(56), RGB_TO_CURSES(117), RGB_TO_CURSES(161));
		init_pair(NB_COLORS + BLUE2, BLUE2, COLOR_BLACK);
		init_color(PURPLE2, RGB_TO_CURSES(117), RGB_TO_CURSES(22), RGB_TO_CURSES(186));
		init_pair(NB_COLORS + PURPLE2, PURPLE2, COLOR_BLACK);
		init_color(PINK, RGB_TO_CURSES(245), RGB_TO_CURSES(147), RGB_TO_CURSES(216));
		init_pair(NB_COLORS + PINK, PINK, COLOR_BLACK);
		clear();
	}
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	for (int i = 0; i < FILENAME_LEN; i++)
		display->letter_filename[i] = FILENAME[i];
}
