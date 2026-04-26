#include "wkw.h"

void	print_score(int score, int row, int col);


void	ft_mvwaddstr(WINDOW *win, int x, int y, char *str, int attrs)
{
	wattron(win, attrs);
	mvwaddstr(win, x, y, (const char *)str);
	wattroff(win, attrs);
}


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

	for (int row = 0; row < display->board.size; row++)
	{
		for (int col = 0; col < display->board.size; col++)
		{
			if (display->board.tiles[row][col] > max_nb)
				max_nb = display->board.tiles[row][col];
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


void	display_endgame(t_display *display)
{
	int	row, col, msg_length;

	row = display->start_row;
	if (display->endgame_ascii_banner)
	{
		print_ascii_art(row, display->start_col, ENGAME_FILENAME, ENDGAME_WIDTH);
		row += ENDGAME_HEIGHT;
	}
	else
	{
		col = display->start_col + (display->width - strlen(ENDGAME_MSG)) / 2;
		mvwaddstr(stdscr, row, col, ENDGAME_MSG);
		row += 2;
	}
	if (display->endgame_score)
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
		display->width += MENU_WIDTH - display_width;
	}
	display->start_row = (LINES - display->height) / 2;
	display->start_col = (COLS - display->width) / 2;
	display_menu(display);
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


void	display_menu(t_display *display)
{
	int	row, col, msg_length;

	clear();
	row = display->start_row;
	if (display->menu_ascii_banner)
	{
		print_ascii_art(row, display->start_col, MENU_FILENAME, MENU_WIDTH);
		row += MENU_HEIGHT + 1;
	}
	if (display->menu_score)
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


void	display_scores(t_display *display)
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


void	display_numbers(t_display *display)
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
}
