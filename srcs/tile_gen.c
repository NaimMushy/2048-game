/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:35:02 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 18:15:44 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wkw.h"

enum e_error	add_tile(t_board* ptr_board)
{
	int		new_tile, tile_pos, i, j;
 
	if (rand() % 5 == 4)
		new_tile = 4;
	else
		new_tile = 2;	
	tile_pos = rand() % ptr_board->nb_empty_tiles;
	i = 0;
	while (i < ptr_board->size)
	{
		j = 0;
		while (j < ptr_board->size)
		{
			if (ptr_board->tiles[i][j] == 0)
			{
				if (tile_pos == 0)
				{
					ptr_board->tiles[i][j] = new_tile;
					--ptr_board->nb_empty_tiles;
					return (SUCCESS);
				}
				--tile_pos;
			}
			++j;
		}
		++i;
	}
	return (ERROR_GAME);
}
