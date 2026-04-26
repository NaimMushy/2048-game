#ifndef WKW_H
# define WKW_H

# define TOO_SMALL_MSG "GAME WINDOW TOO SMALL"
# define SCORE_MSG "SCORE: "
# define BEST_SCORE_MSG "BEST SCORE: "
# define PLAY_MSG "> PLAY"
# define QUIT_MSG "> QUIT"
# define ENDGAME_MSG "END OF GAME"
# define STARTOVER_MSG "> start over"
# define CONTINUE_MSG "> continue game"
# define QUITGAME_MSG "> quit game"
# define MAX_BOARD_SIZE 10
# define SCORE_FILENAME "best_score.txt"
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
# define ENTER_KEY 10
# define DEFAULT_SIZE 4

# include <stdbool.h>
# include <ncurses.h>
# include <string.h>
# include <stddef.h>
# include "colors.h"
# include "get_next_line.h"


enum	e_const
{
	WIN_VALUE = 8
};

enum	e_states
{
	MENU,
	GAME,
	ENDGAME
};

enum	e_options
{
	PLAY_OPTION,
	QUIT_OPTION,
	STARTOVER_OPTION,
	CONTINUE_OPTION,
	QUITGAME_OPTION
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

typedef struct	s_display
{
	t_board	board;
	int		width;
	int		height;
	int		start_row;
	int		start_col;
	int		state;
	int		option_selected;
	bool	ascii;
	bool	quit;
	bool	menu_score;
	bool	menu_ascii_banner;
	bool	endgame_score;
	bool	endgame_ascii_banner;
	char	letter_filename[FILENAME_LEN];
}	t_display;


void	init_display(t_display *display);
void	handle_resize(void);
void	display_menu(t_display *display);
void	resize_menu(t_display *display);
void	display_board(t_display *display);
void	resize_board(t_display *display);
void	save_score(int score);
int		intlen(int number);
int		ft_pow(int to_pow, int power);
int		game_loop(t_board *board, int input);
int		game_init(t_board *board, int size);

#endif
