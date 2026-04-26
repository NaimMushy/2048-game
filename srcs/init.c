#include "wkw.h"
#include "game_mechs.h"

static int	set_win_value(void);
static void	init_colors(void);

void	init_display(t_display *display)
{
	initscr();
	if (has_colors())
		init_colors();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	display->letter.filename = LETTER_FILENAME;
	display->letter.width = LETTER_WIDTH;
	display->letter.height = LETTER_HEIGHT;
	display->menu.filename = MENU_FILENAME;
	display->menu.width = MENU_WIDTH;
	display->menu.height = MENU_HEIGHT;
	display->endgame.filename = ENDGAME_FILENAME;
	display->endgame.width = ENDGAME_WIDTH;
	display->endgame.height = ENDGAME_HEIGHT;
	display->state = MENU;
	display->option_selected = PLAY_OPTION;
	display->board.size = DEFAULT_SIZE;
	display->board.max_score = read_score();
	display->quit = false;
}

static void	init_colors(void)
{
	start_color();
	init_color(RED1, RGB_TO_CURSES(153), RGB_TO_CURSES(33), RGB_TO_CURSES(17));
	init_pair(NB_COLORS + RED1, RED1, COLOR_BLACK);
	init_color(ORANGE, RGB_TO_CURSES(191), RGB_TO_CURSES(85), RGB_TO_CURSES(13));
	init_pair(NB_COLORS + ORANGE, ORANGE, COLOR_BLACK);
	init_color(YELLOW1, RGB_TO_CURSES(212), RGB_TO_CURSES(169), RGB_TO_CURSES(15));
	init_pair(NB_COLORS + YELLOW1, YELLOW1, COLOR_BLACK);
	init_color(GREEN1, RGB_TO_CURSES(107), RGB_TO_CURSES(173), RGB_TO_CURSES(68));
	init_pair(NB_COLORS + GREEN1, GREEN1, COLOR_BLACK);
	init_color(BLUE1, RGB_TO_CURSES(68), RGB_TO_CURSES(173), RGB_TO_CURSES(166));
	init_pair(NB_COLORS + BLUE1, BLUE1, COLOR_BLACK);
	init_color(PURPLE1, RGB_TO_CURSES(99), RGB_TO_CURSES(64), RGB_TO_CURSES(130));
	init_pair(NB_COLORS + PURPLE1, PURPLE1, COLOR_BLACK);
	init_color(RED2, RGB_TO_CURSES(245), RGB_TO_CURSES(53), RGB_TO_CURSES(39));
	init_pair(NB_COLORS + RED2, RED2, COLOR_BLACK);
	init_color(GREEN2, RGB_TO_CURSES(43), RGB_TO_CURSES(128), RGB_TO_CURSES(71));
	init_pair(NB_COLORS + GREEN2, GREEN2, COLOR_BLACK);
	init_color(BLUE2, RGB_TO_CURSES(56), RGB_TO_CURSES(117), RGB_TO_CURSES(161));
	init_pair(NB_COLORS + BLUE2, BLUE2, COLOR_BLACK);
	init_color(PURPLE2, RGB_TO_CURSES(117), RGB_TO_CURSES(22), RGB_TO_CURSES(186));
	init_pair(NB_COLORS + PURPLE2, PURPLE2, COLOR_BLACK);
	init_color(PINK, RGB_TO_CURSES(245), RGB_TO_CURSES(147), RGB_TO_CURSES(216));
	init_pair(NB_COLORS + PINK, PINK, COLOR_BLACK);
	clear();
}

enum e_error	game_init(t_board* ptr_board, int board_size)
{
	if (board_size > MAX_BOARD_SIZE)
		return (ERROR_GAME);
	ptr_board->win_value = set_win_value();
	ptr_board->size = board_size;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			ptr_board->tiles[i][j] = 0;
		}
	}
	ptr_board->nb_empty_tiles = board_size * board_size;
	srand(time(0));
	add_tile(ptr_board);
	add_tile(ptr_board);
	ptr_board->game_status = RUNNING;
	ptr_board->player_score = 0;
	return (SUCCESS);
}

static int	set_win_value(void)
{
	int	win_value = 2;

	while (win_value < WIN_VALUE)
		win_value *= 2;
	if (win_value == WIN_VALUE)
		return (WIN_VALUE);
	return (2048);
}
