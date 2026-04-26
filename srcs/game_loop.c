/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:49:57 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 18:15:00 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static bool			process_line(t_board* ptr_board, int* line);
static void			get_line(t_board* ptr_board, int* line, int input, int index);
static void			set_line(t_board* ptr_board, int* line, int input, int index);
static void			check_win_status(t_board* ptr_board);
static void			check_game_over(t_board* ptr_board);

enum e_error	game_loop(t_board* ptr_board, int input)
{
	int		line[MAX_BOARD_SIZE];
	bool	input_valid = false;

	for (int i = 0; i < ptr_board->size; ++i)
	{
		get_line(ptr_board, line, input, i);
		if (process_line(ptr_board, line) == true)
		{
			input_valid = true;
			set_line(ptr_board, line, input, i);
		}
	}
	if (input_valid == true && add_tile(ptr_board) != SUCCESS)
		return (ERROR_GAME);
	if (ptr_board->game_status == RUNNING)
		check_win_status(ptr_board);
	check_game_over(ptr_board);
	return (SUCCESS);
}

static bool	process_line(t_board* ptr_board, int* line)
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

static void	get_line(t_board* ptr_board, int* line, int input, int index)
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

static void	set_line(t_board* ptr_board, int* line, int input, int index)
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

static void	check_win_status(t_board* ptr_board)
{
	for (int i = 0; i < ptr_board->size; ++i)
	{
		for (int j = 0; j < ptr_board->size; ++j)
		{
			if (ptr_board->tiles[i][j] == WIN_VALUE)
				ptr_board->game_status = WIN;
		}
	}
}

static void	check_game_over(t_board* ptr_board)
{
	if (ptr_board->nb_empty_tiles == 0)
	{
		for (int i = 0; i < ptr_board->size; ++i)
		{
			for (int j = 0; j < ptr_board->size; ++j)
			{
				if (i + 1 < ptr_board->size && ptr_board->tiles[i][j] == ptr_board->tiles[i + 1][j])
					return ;
				if (j + 1 < ptr_board->size && ptr_board->tiles[i][j] == ptr_board->tiles[i][j + 1])
					return ;
			}
		}
		ptr_board->game_status = GAME_OVER;
	}
}
