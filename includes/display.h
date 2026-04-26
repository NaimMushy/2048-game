#ifndef DISPLAY_H
# define DISPLAY_H

// -------------------- DEFINES ------------------------//

# define TOO_SMALL_MSG "GAME WINDOW TOO SMALL"
# define SCORE_MSG "SCORE: "
# define BEST_SCORE_MSG "BEST SCORE: "
# define PLAY_MSG "> PLAY"
# define QUIT_MSG "> QUIT"
# define ENDGAME_MSG "END OF GAME"
# define STARTOVER_MSG "> start over"
# define CONTINUE_MSG "> continue game"
# define QUITGAME_MSG "> quit game"
# define LETTER_FILENAME "srcs/letters/letter_0.txt"
# define LETTER_FILENAME_POS 20
# define LETTER_WIDTH 6
# define LETTER_HEIGHT 5
# define MENU_FILENAME "srcs/ascii_banners/title1.txt"
# define MENU_WIDTH 58
# define MENU_HEIGHT 8
# define ENDGAME_FILENAME "srcs/ascii_banners/end_game.txt"
# define ENDGAME_WIDTH 59
# define ENDGAME_HEIGHT 8

// -------------------- INCLUDES ------------------------//

# include "wkw.h"
# include "colors.h"

// -------------------- STRUCTURES ------------------------//

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

typedef struct	s_banner
{
	bool	score;
	bool	ascii;
	int		width;
	int		height;
	char	*filename;
}	t_banner;

typedef struct	s_display
{
	t_board		board;
	int			width;
	int			height;
	int			start_row;
	int			start_col;
	int			state;
	int			option_selected;
	bool		quit;
	t_banner	menu;
	t_banner	endgame;
	t_banner	letter;
}	t_display;


// -------------------- FUNCTION PROTOTYPES ---------------------//

void	init_display(t_display *display);

void	ft_mvwaddstr(WINDOW *win, int x, int y, char *str, int attrs);
void	choose_letter_type(t_display *display);

void	print_ascii_art(int row, int col, char *filename, int line_len);
void	print_corner(int row, int col, int cur_row, int cur_col, int board_sz);
void	print_score(int score, int row, int col);
void	print_char_with_color(int row, int col, char character, int color);
void	print_ascii_number(int row, int col, t_display *display, int number);
void	print_single_number(int row, int col, t_display *display);

void	display_endgame(t_display *display);
void	display_menu(t_display *display);
void	display_board(t_display *display);

void	handle_resize(void);
void	resize_board(t_display *display);
void	resize_menu(t_display *display);
void	resize_endgame(t_display *display);

#endif
