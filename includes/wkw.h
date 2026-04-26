#ifndef WKW_H
# define WKW_H

# define TOO_SMALL_MSG "GAME WINDOW TOO SMALL"
# define SCORE_MSG "SCORE: "
# define BEST_SCORE_MSG "BEST SCORE: "
# define MAX_SIZE 10
# define FILENAME "srcs/letters/letter_0.txt"
# define FILENAME_LEN 25
# define LETTER_FILENAME 20
# define LETTER_WIDTH 6
# define LETTER_HEIGHT 5

# include <stdbool.h>
# include <ncurses.h>
# include <string.h>
# include "colors.h"
# include "get_next_line.h"

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
	int		board[MAX_SIZE][MAX_SIZE];
	int		board_sz;
	int		width;
	int		height;
	int		start_row;
	int		start_col;
	int		player_score;
	int		best_score;
	bool	ascii;
	char	letter_filename[FILENAME_LEN];
}	t_display;


void	init_display(void);
void	handle_resize(void);
void	change_board(t_display *display, int new_board[MAX_SIZE][MAX_SIZE]);
void	display_board(t_display *display);
int		resize_window(t_display *display);

#endif
