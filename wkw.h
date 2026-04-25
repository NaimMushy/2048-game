#ifndef WKW_H
# define WKW_H

# include <stdbool.h>

enum	e_const
{
	WIN_VALUE = 2048
}

typedef struct	s_tile
{
	size_t	number;
	bool	is_empty;
	bool	has_merged;
}	t_tile;

typedef struct	s_board
{
	t_tiles	**tiles;
	size_t	max_score;
	size_t	player_score;
	bool	is_over;
}	t_board;
