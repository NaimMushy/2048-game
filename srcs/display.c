#include "wkw.h"

void	display_board(t_display *display);

void	handle_resize(void)
{
	endwin();
	refresh();
	clear();
}


int	intlen(int nb)
{
	int	count = 1;

	while ((nb = nb / 10) != 0)
		count++;
	return (count);
}


int	ft_pow(int to_pow, int power)
{
	int	return_pow = 1;

	while (--power > 0)
		return_pow = return_pow * to_pow;
	return (return_pow);
}


int	get_max_nb(t_display *display)
{
	int	max_nb = 0;

	for (int row = 0; row < display->board_sz; row++)
	{
		for (int col = 0; col < display->board_sz; col++)
		{
			if (display->board[row][col] > max_nb)
				max_nb = display->board[row][col];
		}
	}
	return (max_nb);
}


int	get_multiple(int divide, int number)
{
	int	count = 0;

	while ((number = number / divide) > 1)
		count++;
	return (count);
}


void	choose_letter_type(t_display *display)
{
	int	max_len = intlen(get_max_nb(display));

	if (display->height <= 2 + LETTER_HEIGHT)
		display->ascii = false;
	else if (display->width <= 2 + (LETTER_WIDTH * max_len) + (max_len - 1))
		display->ascii = false;
	else
		display->ascii = true;
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

void	resize_board(t_display *display)
{
	int	offset = 5;
	int	min_sz = 2 + intlen(get_max_nb(display));

	handle_resize();
	display->width = (COLS - offset) / (display->board_sz * 2);
	display->height = (LINES  - offset) / display->board_sz;
	while (offset-- > 0 && display->width < min_sz && display->height < min_sz)
	{
		display->width = (COLS - offset) / (display->board_sz * 2);
		display->height = (LINES  - offset) / display->board_sz;
	}
	if (display->width < min_sz || display->height < min_sz)
	{
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		return ;
	}
	if (display->width <= display->height)
		display->height = display->width;
	display->width = display->height * 2;
	display->start_row = (LINES - (display->height * display->board_sz)) / 2;
	display->start_col = (COLS - (display->width * display->board_sz)) / 2;
	display_board(display);
}


void	display_scores(t_display *display)
{
	int	msg_length, score_len, score, power, digit, pos;

	if (LINES <= display->height * display->board_sz + 1)
		return ;
	score = display->player_score;
	score_len = intlen(score);
	msg_length = strlen(SCORE_MSG) + score_len + 3 + strlen(BEST_SCORE_MSG) + intlen(display->best_score);
	if (COLS < msg_length)
		return ;
	pos = (COLS - msg_length) / 2;
	mvwaddstr(stdscr, 1, pos, SCORE_MSG);
	pos = pos + strlen(SCORE_MSG);
	while (score_len)
	{
		power = ft_pow(10, score_len);
		digit = score / power;
		mvwaddch(stdscr, 1, pos, (char)digit + '0');
		pos++;
		score = score - (digit * power);
		score_len--;
	}
	pos = pos + 3;
	mvwaddstr(stdscr, 1, pos, BEST_SCORE_MSG);
	pos = pos + strlen(BEST_SCORE_MSG);
	score = display->best_score;
	score_len = intlen(display->best_score);
	while (score_len)
	{
		power = ft_pow(10, score_len);
		digit = score / power;
		mvwaddch(stdscr, 1, pos, (char)digit + '0');
		pos++;
		score = score - (digit * power);
		score_len--;
	}
}


void	print_char_with_color(int row, int col, char character, int color)
{
	wattron(stdscr, COLOR_PAIR(NB_COLORS + color));
	mvwaddch(stdscr, row, col, character);
	wattroff(stdscr, COLOR_PAIR(NB_COLORS + color));
}


void	print_ascii_number(int row, int col, t_display *display, int number)
{
	int fd;
	char *line;

	display->letter_filename[LETTER_FILENAME] = (char)number + '0';
	fd = open(display->letter_filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		for (int char_index = 0; char_index < LETTER_WIDTH; char_index++)
			print_char_with_color(row, col + char_index, line[char_index], START_COLOR + char_index);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
}


void	print_single_number(int row, int col, t_display *display)
{
	int 	nb_row, nb_col, digit;
	int		number = display->board[row][col];
	int		len = intlen(number);

	nb_row = display->start_row + (row * display->height) + 1;
	nb_col = display->start_col + (col * display->width) + 1;
	if (display->ascii)
	{
		nb_row = nb_row + ((display->height - LETTER_HEIGHT) / 2);
		nb_col = nb_col + ((display->width - (LETTER_WIDTH * len + len - 1)) / 2);
	}
	else
	{
		nb_row = nb_row + ((display->height - 1) / 2);
		nb_col = nb_col + ((display->width - len) / 2);
	}
	while (len > 0)
	{
		digit = number / ft_pow(10, len);
		if (display->ascii)
		{
			print_ascii_number(nb_row, nb_col, display, digit);
			nb_col = nb_col + LETTER_WIDTH;
		}
		else
			print_char_with_color(nb_row, nb_col, (char)digit + '0', START_COLOR + (get_multiple(2, display->board[row][col]) % NB_COLORS));
		nb_col++;
		number = number - (digit * ft_pow(10, len));
		len--;
	}
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
	choose_letter_type(display);
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
	display_scores(display);
}



// void	ft_mvaddstr(WINDOW *win, int x, int y, char *str, int attrs)
// {
// 	wattron(win, attrs);
// 	mvwaddstr(win, x, y, (const char *)str);
// 	wattroff(win, attrs);
// }


void	change_board(t_display *display, int new_board[MAX_SIZE][MAX_SIZE])
{
	for (int i = 0; i < display->board_sz; i++)
	{
		for (int j = 0; j < display->board_sz; j++)
			display->board[i][j] = new_board[i][j];
	}
}
