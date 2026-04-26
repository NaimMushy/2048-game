/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:10:44 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 20:11:47 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

bool	process_line(t_board* ptr_board, int* line)
{
	int		new_pos;
	bool	change = false;
	
	for (int i = 0; i < ptr_board->size; ++i)
	{
		if (line[i] != 0)
		{
			for (int j = i + 1; j < ptr_board->size; ++j)
			{
				if (line[j] != 0)
				{
					if (line[i] == line[j])
					{
						line[i] <<= 1;
						ptr_board->player_score += line[i];
						if (ptr_board->player_score > ptr_board->max_score)
							ptr_board->max_score = ptr_board->player_score;
						line[j] = 0;
						++ptr_board->nb_empty_tiles;
						change = true;
					}
					break ;
				}
			}
			new_pos = i;
			while (new_pos > 0 && line[new_pos - 1] == 0)
				--new_pos;
			if (new_pos != i)
			{
				line[new_pos] = line[i];
				line[i] = 0;
				change = true;
			}	
		}
	}
	return (change);
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
