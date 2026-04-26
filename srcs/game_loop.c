/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:49:57 by cviel             #+#    #+#             */
/*   Updated: 2026/04/25 19:27:52 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include "wkw.h"

void	process_line(t_board* ptr_board, int* line);
void	get_line(t_board* ptr_board, int* line, int input, int index);
void	set_line(t_board* ptr_board, int* line, int input, int index);
int		add_tile(t_board* ptr_board);

int	game_loop(t_board* ptr_board, int input)
{
	int	line[MAX_BOARD_SIZE];

	if (input == 0)
		return (1);
	for (int i = 0; i < ptr_board->size; ++i)
	{
		get_line(ptr_board, line, input, i);
		process_line(ptr_board, line);
		set_line(ptr_board, line, input, i);
	}
	return (add_tile(ptr_board));
}

void	process_line(t_board* ptr_board, int* line)
{
	int	new_pos;
	
	for (int i = 0; i < ptr_board->size - 1; ++i)
	{
		for (int j = i + 1; j < ptr_board->size; ++j)
		{
			if (line[i] != 0)
			{
				if (line[i] == line[j])
				{
					line[i] <<= 1;
					ptr_board->player_score += line[i];
					line[j] = 0;
					++ptr_board->nb_empty_tiles;
				}
				break ;
			}
		}
		new_pos = i;
		while (new_pos > 0 && line[new_pos - 1] != 0)
			--new_pos;
		if (new_pos != i)
		{
			line[new_pos] = line[i];
			line[i] = 0;
		}
	}
}

void	get_line(t_board* ptr_board, int* line, int input, int index)
{
	int	row, col;
	
	for (int i = 0; i < ptr_board->size; ++i)
	{
		switch (input)
		{
			case KEY_UP:
			{
				row = i;
				col = index;
				break ;
			}
			case KEY_DOWN:
			{
				row = ptr_board->size - i - 1;
				col = index;
				break ;
			}
			case KEY_LEFT:
			{
				row = index;
				col = i;
				break ;
			}
			case KEY_RIGHT:
			{
				row = index;
				col = ptr_board->size - i - 1;
				break ;
			}
		}
		line[i] = ptr_board->tiles[row][col];
	}
}

void	set_line(t_board* ptr_board, int* line, int input, int index)
{
	int	row, col;
	
	for (int i = 0; i < ptr_board->size; ++i)
	{
		switch (input)
		{
			case KEY_UP:
			{
				row = i;
				col = index;
				break ;
			}
			case KEY_DOWN:
			{
				row = ptr_board->size - i - 1;
				col = index;
				break ;
			}
			case KEY_LEFT:
			{
				row = index;
				col = i;
				break ;
			}
			case KEY_RIGHT:
			{
				row = index;
				col = ptr_board->size - i - 1;
				break ;
			}
		}
		ptr_board->tiles[row][col] = line[i];
	}
}
