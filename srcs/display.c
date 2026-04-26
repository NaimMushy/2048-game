#include "wkw.h"

static void	display_numbers(t_display *display);
static void	display_scores(t_display *display);


void	display_endgame(t_display *display)
{
	int	row, col, msg_length;

	clear();
	row = display->start_row;
	if (display->endgame.ascii)
	{
		print_ascii_art(row, display->start_col, display->endgame.filename, display->endgame.width);
		row += display->endgame.height + 3;
	}
	else
	{
		col = display->start_col + (display->width - strlen(ENDGAME_MSG)) / 2;
		mvwaddstr(stdscr, row, col, ENDGAME_MSG);
		row += 2;
	}
	if (display->endgame.score)
	{
		msg_length = strlen(SCORE_MSG) + intlen(display->board.player_score);
		col = display->start_col + (display->width - msg_length) / 2;
		mvwaddstr(stdscr, row, col, SCORE_MSG);
		col += strlen(SCORE_MSG);
		print_score(display->board.player_score, row, col);
		row += 2;
	}
	col = display->start_col + (display->width - strlen(STARTOVER_MSG)) / 2;
	if (display->option_selected == STARTOVER_OPTION)
		ft_mvwaddstr(stdscr, row, col, STARTOVER_MSG, A_UNDERLINE);
	else
		mvwaddstr(stdscr, row, col, STARTOVER_MSG);
	row += 2;
	if (display->board.game_status == WIN)
	{
		col = display->start_col + (display->width - strlen(CONTINUE_MSG)) / 2;
		if (display->option_selected == CONTINUE_OPTION)
			ft_mvwaddstr(stdscr, row, col, CONTINUE_MSG, A_UNDERLINE);
		else
			mvwaddstr(stdscr, row, col, CONTINUE_MSG);
		row += 2;
	}
	col = display->start_col + (display->width - strlen(QUITGAME_MSG)) / 2;
	if (display->option_selected == QUITGAME_OPTION)
		ft_mvwaddstr(stdscr, row, col, QUITGAME_MSG, A_UNDERLINE);
	else
		mvwaddstr(stdscr, row, col, QUITGAME_MSG);
	refresh();
}

/*
void	display_size_choice(t_display *display)
{

}
*/


void	display_menu(t_display *display)
{
	int	row, col, msg_length;

	clear();
	row = display->start_row;
	if (display->menu.ascii)
	{
		print_ascii_art(row, display->start_col, display->menu.filename, display->menu.width);
		row += display->menu.height + 1;
	}
	if (display->menu.score)
	{
		msg_length = strlen(BEST_SCORE_MSG) + intlen(display->board.max_score);
		col = display->start_col + (display->width - msg_length) / 2;
		mvwaddstr(stdscr, row, col, BEST_SCORE_MSG);
		col += strlen(BEST_SCORE_MSG);
		print_score(display->board.max_score, row, col);
		row += 2;
	}
	col = display->start_col + (display->width - strlen(PLAY_MSG)) / 2;
	if (display->option_selected == PLAY_OPTION)
		ft_mvwaddstr(stdscr, row, col, PLAY_MSG, A_UNDERLINE);
	else
		mvwaddstr(stdscr, row, col, PLAY_MSG);
	row += 2;
	col = display->start_col + (display->width - strlen(QUIT_MSG)) / 2;
	if (display->option_selected == QUIT_OPTION)
		ft_mvwaddstr(stdscr, row, col, QUIT_MSG, A_UNDERLINE);
	else
		mvwaddstr(stdscr, row, col, QUIT_MSG);
	refresh();
}


static void	display_scores(t_display *display)
{
	int	msg_length, pos;

	if (LINES <= display->height * display->board.size + 1)
		return ;
	msg_length = strlen(SCORE_MSG) + intlen(display->board.player_score) + 3 + strlen(BEST_SCORE_MSG) + intlen(display->board.max_score);
	if (COLS < msg_length)
		return ;
	pos = (COLS - msg_length) / 2;
	mvwaddstr(stdscr, 1, pos, SCORE_MSG);
	pos = pos + strlen(SCORE_MSG);
	print_score(display->board.player_score, 1, pos);
	pos = pos + 3;
	mvwaddstr(stdscr, 1, pos, BEST_SCORE_MSG);
	pos = pos + strlen(BEST_SCORE_MSG);
	print_score(display->board.max_score, 1, pos);
}


static void	display_numbers(t_display *display)
{
	int row, col;

	row = -1;
	while (++row < display->board.size)
	{
		col = -1;
		while (++col < display->board.size)
		{
			if (display->board.tiles[row][col] > 0)
				print_single_number(row, col, display);
		}
	}
}


void	display_board(t_display *display)
{
	int row, col, cur_row, cur_col;

	clear();
	choose_letter_type(display);
	row = -1;
	while (++row <= display->board.size)
	{
		cur_row = display->start_row + (row * display->height);
		col = -1;
		while (++col <= display->board.size)
		{
			cur_col = display->start_col + (col * display->width);
			print_corner(row, col, cur_row, cur_col, display->board.size);
			if (col < display->board.size)
				mvwhline(stdscr, cur_row, cur_col + 1, ACS_HLINE, display->width - 1);
			if (row < display->board.size)
				mvwvline(stdscr, cur_row + 1, cur_col, ACS_VLINE, display->height - 1);
		}
	}
	display_numbers(display);
	display_scores(display);
	refresh();
}
