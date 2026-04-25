#ifndef WKW_H
# define WKW_H

# include <stdbool.h>
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>
# include "borders.h"

enum	e_const
{
	WIN_VALUE = 2048
};

typedef struct	s_tile
{
	size_t	number;
	bool	is_empty;
	bool	has_merged;
}	t_tile;

typedef struct	s_board
{
	t_tile	**tiles;
	size_t	max_score;
	size_t	player_score;
	bool	is_over;
}	t_board;

typedef struct	s_display
{
	int		**board;
	int		width;
	int		height;
	int		start_row;
	int		start_col;
	int		board_sz;
}	t_display;

#endif
