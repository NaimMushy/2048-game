/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:15:43 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 18:14:22 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "wkw.h"

void	add_tile(t_board *board);
int		set_win_value(void);

int	read_score(void)
{
	int		fd = open(SCORE_FILENAME, O_RDONDLY);
	int		ret = 1;
	int		score = 0;
	char	buf;

	if (fd < 0)
		return (0);
	if (fd <= 2)
	{
		close(fd);
		return (0);
	}
	while (ret > 0)
	{
		ret = read(fd, buf, 1);
		if (buf < '0' || buf > '9')
			return (0);
		score = score * 10 + (buf - '0');
	}
	close(fd);
	if (ret < 0)
		return (0);
	return (score);
}

void	save_score(int score)
{
	int	len = intlen(score);
	int	digit, power;
	int fd = open(SCORE_FILENAME, O_WRONLY | O_TRUNC | O_CREAT);

	if (fd < 0)
		return (0);
	if (fd <= 2)
	{
		close(fd);
		return (0);
	}
	while (len)
	{
		power = ft_pow(10, len);
		digit = score / power;
		write(fd, (char)digit + '0', 1);
		score = score - (digit * power);
		len--;
	}
	close(fd);
}

int	game_init(t_board* ptr_board, int board_size)
{
	if (board_size > MAX_BOARD_SIZE)
		return (ERROR_GAME);
	ptr_board->win_value = set_win_value();
	ptr_board->size = board_size;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			ptr_board->tiles[i][j] = 0;
		}
	}
	
	ptr_board->nb_empty_tiles = board_size * board_size;
	srand(time(0));
	add_tile(ptr_board);
	add_tile(ptr_board);
	ptr_board->game_status = RUNNING;
	ptr_board->player_score = 0;
	ptr_board->max_score = read_score();
	return (SUCCESS);
}

int	set_win_value(void)
{
	int	win_value = 2;

	while (win_value < WIN_VALUE)
		win_value *= 2;
	if (win_value == WIN_VALUE)
		return (WIN_VALUE);
	return (2048);
}