#include "wkw.h"


void	handle_resize(void)
{
	endwin();
	refresh();
	clear();
}


void	resize_board(t_display *display)
{
	int	offset = 5;
	int	min_sz = 2 + intlen(get_max_nb(display));

	handle_resize();
	display->width = (COLS - offset) / (display->board.size * 2);
	display->height = (LINES  - offset) / display->board.size;
	while (offset-- > 0 && display->width < min_sz && display->height < min_sz)
	{
		display->width = (COLS - offset) / (display->board.size * 2);
		display->height = (LINES  - offset) / display->board.size;
	}
	if (display->width < min_sz || display->height < min_sz)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (display->width <= display->height)
		display->height = display->width;
	display->width = display->height * 2;
	display->start_row = (LINES - (display->height * display->board.size)) / 2;
	display->start_col = (COLS - (display->width * display->board.size)) / 2;
	display_board(display);
}


void	resize_menu(t_display *display)
{
	int	msg_length = (strlen(BEST_SCORE_MSG) + intlen(display->board.max_score));

	handle_resize();
	display->height = 3;
	display->width = 7;
	display->menu_score = false;
	display->menu_ascii_banner = false;
	if (LINES < display->height || COLS < display->width)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (LINES >= display->height + 2 && COLS >= display->width + (msg_length - display->width))
	{
		display->menu_score = true;
		display->height += 2;
		display->width += msg_length - display->width;
	}
	if (LINES >= display->height + MENU_HEIGHT + 1 && COLS >= display->width + (MENU_WIDTH - display->width))
	{
		display->menu_ascii_banner = true;
		display->height += MENU_HEIGHT + 1;
		display->width += MENU_WIDTH - display->width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_menu(display);
}


void	resize_endgame(t_display *display)
{
	int	msg_length = strlen(SCORE_MSG) + intlen(display->board.player_score);

	handle_resize();
	display->height = 7;
	display->width = 13;
	if (display->board.game_status == WIN)
	{
		display->height += 2;
		display->width += 3;
	}
	display->endgame_ascii_banner = false;
	if (LINES < display->height || COLS < display->width)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (LINES >= display->height + 2 && COLS >= display->width + (msg_length - display->width))
	{
		display->endgame_score = true;
		display->height += 2;
		display->width += msg_length - display->width;
	}
	if (LINES >= display->height + ENDGAME_HEIGHT -1 && COLS >= display->width + (ENDGAME_WIDTH) - display->width)
	{
		display->endgame_ascii_banner = true;
		display->height += ENDGAME_HEIGHT - 1;
		display->width += ENDGAME_WIDTH - display->width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_endgame(display);
}
