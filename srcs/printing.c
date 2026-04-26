#include "wkw.h"


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


void	print_ascii_art(int row, int col, char *filename, int line_len)
{
	int 	fd = open(filename, O_RDONLY);
	char	*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		mvwaddnstr(stdscr, row, col, line, line_len);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
}


void	print_score(int score, int row, int col)
{
	int power, digit, score_len;

	score_len = intlen(score);
	while (score_len)
	{
		power = ft_pow(10, score_len);
		digit = score / power;
		mvwaddch(stdscr, row, col, (char)digit + '0');
		col++;
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
	int		number = display->board.tiles[row][col];
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
			print_char_with_color(nb_row, nb_col, (char)digit + '0', START_COLOR + (get_multiple(2, display->board.tiles[row][col]) % NB_COLORS));
		nb_col++;
		number = number - (digit * ft_pow(10, len));
		len--;
	}
}
