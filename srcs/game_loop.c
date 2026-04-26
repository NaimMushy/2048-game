/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:49:57 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 20:15:37 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"
#include "game_mechs.h"

static void	check_win_status(t_board* ptr_board);
static void	check_game_over(t_board* ptr_board);

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
