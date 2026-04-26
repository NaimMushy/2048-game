#ifndef WKW_H
# define WKW_H

// -------------------- DEFINES ------------------------//

# define MAX_BOARD_SIZE 10
# define DEFAULT_SIZE 4
# define SCORE_FILENAME "best_score.txt"
# define ESCAPE_KEY 27
# define ENTER_KEY 10

// -------------------- STRUCTURES ------------------------//

enum	e_const
{
	WIN_VALUE = 8
};

enum	e_error
{
	SUCCESS = 0,
	ERROR_NCURSES = 1,
	ERROR_GAME = 2
};

enum e_game_status
{
	RUNNING = 0,
	WIN = 1,
	ENDLESS = 2,
	GAME_OVER = 3,
};

typedef struct	s_board
{
	int					tiles[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
	int					size;
	int					nb_empty_tiles;
	int					max_score;
	int					player_score;
	int					game_status;
	enum e_game_status	win_value;
}	t_board;

// -------------------- INCLUDES ------------------------//

# include <stdbool.h>
# include <ncurses.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include "display.h"
# include "get_next_line.h"

extern bool	g_sig;

// -------------------- FUNCTION PROTOTYPES ---------------------//

int		intlen(int number);
int		get_max_nb(t_display *display);
int		get_multiple(int divide, int number);
int		ft_pow(int to_pow, int power);
int		ft_strlen(char const *s);

void	save_score(int score);
int		read_score(void);

#endif
