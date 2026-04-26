#include <signal.h>
#include "wkw.h"
#include "game_mechs.h"

bool	g_sig = false;

static void		sigint_handler(int sig);
enum e_error	game_handler(t_display *display);
enum e_error	menu_handler(t_display *display);
enum e_error	endgame_handler(t_display *display);

int	main(void)
{
	t_display	display = {0};
	int			ret = SUCCESS;
	
	signal(SIGINT, &sigint_handler);
	init_display(&display);
	while (display.quit == false && !g_sig)
	{
		if (display.state == MENU)
		{
			if ((ret = menu_handler(&display)) != SUCCESS)
				break ;
		}
		else if (display.state == GAME)
		{
			if ((ret = game_handler(&display)) != SUCCESS)
				break ;
		}
		else if (display.state == ENDGAME)
		{
			if ((ret = endgame_handler(&display)) != SUCCESS)
				break ;
		}
	}
	save_score(display.board.max_score);
	endwin();
	return (ret);
}


enum e_error	menu_handler(t_display *display)
{
	int	input, ret;

	resize_menu(display);
	while ((input = wgetch(stdscr)) != ESCAPE_KEY && !g_sig)
	{
		if (input == KEY_RESIZE)
			resize_menu(display);
		else if (input == KEY_DOWN)
		{
			if (display->option_selected == PLAY_OPTION)
			{
				display->option_selected = QUIT_OPTION;
				display_menu(display);
			}
		}
		else if (input == KEY_UP)
		{
			if (display->option_selected == QUIT_OPTION)
			{
				display->option_selected = PLAY_OPTION;
				display_menu(display);
			}
		}
		else if (input == ENTER_KEY)
		{
			if (display->option_selected == PLAY_OPTION)
			{
				display->state = GAME;
				if ((ret = game_init(&display->board, display->board.size)) != SUCCESS)
					return (ret);
				return (SUCCESS);
			}
			else if (display->option_selected == QUIT_OPTION)
			{
				display->quit = true;
				return (SUCCESS);
			}
		}
	}
	display->quit = true;
	return (SUCCESS);
}

enum e_error	game_handler(t_display *display)
{
	int	input, ret;

	resize_board(display);
	while ((input = wgetch(stdscr)) != ESCAPE_KEY && !g_sig)
	{
		if (input == KEY_RESIZE)
			resize_board(display);
		else if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT)
		{
			if ((ret = game_loop(&display->board, input)) != SUCCESS)
				return (ret);
			if (display->board.game_status == RUNNING || display->board.game_status == ENDLESS)
				display_board(display);
			else
			{
				display->state = ENDGAME;
				display->option_selected = STARTOVER_OPTION;
				return (SUCCESS);
			}
		}
	}
	display->state = MENU;
	display->option_selected = PLAY_OPTION;
	return (SUCCESS);
}


enum e_error	endgame_handler(t_display *display)
{
	int	input, ret;

	resize_endgame(display);
	while ((input = wgetch(stdscr)) != ESCAPE_KEY && !g_sig)
	{
		if (input == KEY_RESIZE)
			resize_endgame(display);
		else if (input == KEY_UP)
		{
			if (display->option_selected == QUITGAME_OPTION)
			{
				if (display->board.game_status == WIN)
					display->option_selected = CONTINUE_OPTION;
				else
					display->option_selected = STARTOVER_OPTION;
				display_endgame(display);
			}
			else if (display->option_selected == CONTINUE_OPTION)
			{
				display->option_selected = STARTOVER_OPTION;
				display_endgame(display);
			}
		}
		else if (input == KEY_DOWN)
		{
			if (display->option_selected == STARTOVER_OPTION)
			{
				if (display->board.game_status == WIN)
					display->option_selected = CONTINUE_OPTION;
				else
					display->option_selected = QUITGAME_OPTION;
				display_endgame(display);
			}
			else if (display->option_selected == CONTINUE_OPTION)
			{
				display->option_selected = QUITGAME_OPTION;
				display_endgame(display);
			}
		}
		else if (input == ENTER_KEY)
		{
			if (display->option_selected == STARTOVER_OPTION)
			{
				if ((ret = game_init(&display->board, display->board.size)) != SUCCESS)
					return (ret);
				display->state = GAME;
				return (SUCCESS);
			}
			if (display->option_selected == CONTINUE_OPTION)
			{
				display->board.game_status = ENDLESS;
				display->state = GAME;
				return (SUCCESS);
			}
			if (display->option_selected == QUITGAME_OPTION)
			{
				display->state = MENU;
				display->option_selected = PLAY_OPTION;
				return (SUCCESS);
			}
		}
	}
	display->state = MENU;
	return (SUCCESS);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = true;
}
