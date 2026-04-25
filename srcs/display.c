#include "../includes/wkw.h"

void	handle_resize(void)
{
	endwin();
	refresh();
	clear();
}


void	print_corner(int row, int col, int cur_row, int cur_col, int board_sz)
{
	if (row == 0)
	{
		if (col == 0)
			mvwaddch(stdscr, cur_row, cur_col, ACS_ULCORNER);
		else if (col == board_sz)
			mvwaddch(stdscr, cur_row, cur_col, ACS_URCORNER);
		else
			mvwaddch(stdscr, cur_row, cur_col, ACS_TTEE);
	}
	else if (row == board_sz)
	{
		if (col == 0)
			mvwaddch(stdscr, cur_row, cur_col, ACS_LLCORNER);
		else if (col == board_sz)
			mvwaddch(stdscr, cur_row, cur_col, ACS_LRCORNER);
		else
			mvwaddch(stdscr, cur_row, cur_col, ACS_BTEE);
	}
	else
	{
		if (col == 0)
			mvwaddch(stdscr, cur_row, cur_col, ACS_LTEE);
		else if (col == board_sz)
			mvwaddch(stdscr, cur_row, cur_col, ACS_RTEE);
		else
			mvwaddch(stdscr, cur_row, cur_col, ACS_PLUS);
	}
}


int	resize_window(t_display *display)
{
	display->width = (COLS - 10) / (display->board_sz * 2);
	display->height = (LINES  - 10) / display->board_sz;
	if (display->width == 0 || display->height == 0)
		return (0);
	if (display->width <= display->height)
		display->height = display->width;
	display->width = display->height * 2;
	display->start_row = (LINES - (display->height * display->board_sz)) / 2;
	display->start_col = (COLS - (display->width * display->board_sz)) / 2;
	return (1);
}

char	*get_number_string(int number)
{
	if (number == 2)
		return ("2");
	if (number == 4)
		return ("4");
	if (number == 8)
		return ("8");
	if (number == 16)
		return ("16");
	if (number == 32)
		return ("32");
	if (number == 64)
		return ("64");
	if (number == 128)
		return ("128");
	return ("0");
}


void	print_single_number(int row, int col, t_display *display)
{
	int 	nb_row, nb_col;
	char	*nb_string = get_number_string(display->board[row][col]);

	nb_row = display->start_row + (row * display->height);
	nb_row = nb_row + ((display->height) / 2);
	nb_col = display->start_col + (col * display->width);
	nb_col = nb_col + ((display->width - strlen(nb_string) + 1) / 2);
	mvwaddstr(stdscr, nb_row, nb_col, nb_string);
}


void	display_numbers(t_display *display)
{
	int row, col;

	row = -1;
	while (++row < display->board_sz)
	{
		col = -1;
		while (++col < display->board_sz)
		{
			if (display->board[row][col] > 0)
				print_single_number(row, col, display);
		}
	}
}


void	display_board(t_display *display)
{
	int row, col, cur_row, cur_col;

	clear();
	row = -1;
	while (++row <= display->board_sz)
	{
		cur_row = display->start_row + (row * display->height);
		col = -1;
		while (++col <= display->board_sz)
		{
			cur_col = display->start_col + (col * display->width);
			print_corner(row, col, cur_row, cur_col, display->board_sz);
			if (col < display->board_sz)
				mvwhline(stdscr, cur_row, cur_col + 1, ACS_HLINE, display->width - 1);
			if (row < display->board_sz)
				mvwvline(stdscr, cur_row + 1, cur_col, ACS_VLINE, display->height - 1);
		}
	}
	display_numbers(display);
}



void	ft_mvaddstr(WINDOW *win, int x, int y, char *str, int attrs)
{
	wattron(win, attrs);
	mvwaddstr(win, x, y, (const char *)str);
	wattroff(win, attrs);
}


void	change_board(t_display *display, int new_board[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			display->board[i][j] = new_board[i][j];
	}
}


int	main(void)
{
	int		input = 0;
	char	*too_small = "GAME WINDOW TOO SMALL";
	t_display	game_display = {0};
	int	board1[4][4] = {{2, 0, 4, 8}, {0, 0, 16, 8}, {16, 0, 32, 64}, {2, 2, 16, 4}};
	int	board2[4][4] = {{2, 8, 4, 128}, {2, 0, 16, 2}, {16, 0, 0, 64}, {2, 64, 16, 4}};
	int cur_board = 2;

	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	game_display.board = malloc(sizeof(int *) * 4);
	for (int i = 0; i < 4; i++)
		game_display.board[i] = malloc(sizeof(int) * 4);
	change_board(&game_display, board1);
	game_display.board_sz = 4;
	while (!resize_window(&game_display))
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(too_small)) / 2, too_small);
	display_board(&game_display);
	while ((input = wgetch(stdscr)) != 27)
	{
		if (input == KEY_RESIZE)
		{
			handle_resize();
			while (!resize_window(&game_display))
				mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(too_small)) / 2, too_small);
			display_board(&game_display);
		}
		if (input == 110)
		{
			if (cur_board == 1)
			{
				change_board(&game_display, board1);
				cur_board = 2;
			}
			else
			{
				change_board(&game_display, board2);
				cur_board = 1;
			}
			display_board(&game_display);
		}
	}
	endwin();
	return (1);
}
