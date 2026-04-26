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
# define MENU_FILENAME "srcs/ascii_banners/title1.txt"
# define MENU_WIDTH 58
# define MENU_HEIGHT 8
# define ENDGAME_FILENAME "srcs/ascii_banners/end_game.txt"
# define ENDGAME_WIDTH 59
# define ENDGAME_HEIGHT 8
# define ESCAPE_KEY 27

# include <stdbool.h>
# include <ncurses.h>
# include <string.h>
# include "colors.h"
# include "get_next_line.h"

# define MAX_BOARD_SIZE 10

enum	e_const
{
	WIN_VALUE = 2048
};

enum	e_states
{
	MENU,
	GAME,
	CHOICE
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
	size_t	tiles[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
	size_t	size;
	size_t	nb_empty_tiles;
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
void	resize_board(t_display *display);

#endif
