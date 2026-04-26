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
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - ft_strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
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
	int	msg_length = (ft_strlen(BEST_SCORE_MSG) + intlen(display->board.max_score));

	handle_resize();
	display->height = 3;
	display->width = 7;
	display->menu.score = false;
	display->menu.ascii = false;
	if (LINES < display->height || COLS < display->width)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - ft_strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (LINES >= display->height + 2 && COLS >= display->width + (msg_length - display->width))
	{
		display->menu.score = true;
		display->height += 2;
		display->width += msg_length - display->width;
	}
	if (LINES >= display->height + display->menu.height + 1 && COLS >= display->width + (display->menu.width - display->width))
	{
		display->menu.ascii = true;
		display->height += display->menu.height + 1;
		display->width += display->menu.width - display->width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_menu(display);
}


void	resize_endgame(t_display *display)
{
	int	msg_length = ft_strlen(SCORE_MSG) + intlen(display->board.player_score);

	handle_resize();
	display->height = 7;
	display->width = 13;
	if (display->board.game_status == WIN)
	{
		display->height += 2;
		display->width += 3;
	}
	display->endgame.ascii = false;
	display->endgame.score = false;
	if (LINES < display->height || COLS < display->width)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - ft_strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (LINES >= display->height + 2 && COLS >= display->width + (msg_length - display->width))
	{
		display->endgame.score = true;
		display->height += 2;
		display->width += msg_length - display->width;
	}
	if (LINES >= display->height + display->endgame.height + 3 && COLS >= display->width + (display->endgame.width + 3) - display->width)
	{
		display->endgame.ascii = true;
		display->height += display->endgame.height + 3;
		display->width += display->endgame.width + 3 - display->width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_endgame(display);
}

/*
void	resize_size_choice(t_display *display)
{
	handle_resize();
	display->height = 7;
	display->width = 13;
	if (display->board.game_status == WIN)
	{
		display->height += 2;
		display->width += 3;
	}
	display->endgame.ascii = false;
	display->endgame.score = false;
	if (LINES < display->height || COLS < display->width)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - ft_strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (LINES >= display->height + 2 && COLS >= display->width + (msg_length - display->width))
	{
		display->endgame.score = true;
		display->height += 2;
		display->width += msg_length - display->width;
	}
	if (LINES >= display->height + display->endgame.height + 3 && COLS >= display->width + (display->endgame.width + 3) - display->width)
	{
		display->endgame.ascii = true;
		display->height += display->endgame.height + 3;
		display->width += display->endgame.width + 3 - display->width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_endgame(display);
}
*/
