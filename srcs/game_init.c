/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:15:43 by cviel             #+#    #+#             */
/*   Updated: 2026/04/25 19:26:39 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wkw.h"

int	game_init(t_board* ptr_board, size_t board_size)
{
	if (board_size > MAX_BOARD_SIZE)
		return (ERROR_GAME);
	ptr_board->size = board_size;
	for (size_t i = 0; i < board_size; ++i)
	{
		for (size_t j = 0; j < board_size; ++j)
		{
			ptr_board->tiles[i][j] = 0;
		}
	}
	
	ptr_board->nb_empty_tiles = board_size * board_size;
	srand(time(0));
	add_tile(ptr_board);
	add_tile(ptr_board);
	return (SUCCESS);
}
