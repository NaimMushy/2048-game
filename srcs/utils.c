#include "wkw.h"


void	choose_letter_type(t_display *display)
{
	int	max_len = intlen(get_max_nb(display));

	if (display->height <= 2 + display->letter.height)
		display->letter.ascii = false;
	else if (display->width <= 2 + (display->letter.width * max_len) + (max_len - 1))
		display->letter.ascii = false;
	else
		display->letter.ascii = true;
	display->letter.score = true;
}


void	ft_mvwaddstr(WINDOW *win, int x, int y, char *str, int attrs)
{
	wattron(win, attrs);
	mvwaddstr(win, x, y, (const char *)str);
	wattroff(win, attrs);
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
