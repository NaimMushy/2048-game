#ifndef WKW_H
# define WKW_H

# include <stddef.h>
# include <stdbool.h>

enum	e_const
{
	WIN_VALUE = 2048
};

enum	e_error
{
	SUCCESS = 0,
	ERROR_MALLOC = 1,
	ERROR_NCURSES = 2,
	ERROR_GAME = 3
};

typedef struct	s_board
{
	size_t	**tiles;
	size_t	size;
	size_t	nb_empty_tiles;
	size_t	max_score;
	size_t	player_score;
	bool	is_over;
}	t_board;

#endif