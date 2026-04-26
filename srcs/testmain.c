#include "wkw.h"

void	game_handler(t_display *display);
void	menu_handler(t_display *display);

int	main(void)
{
	t_display	display = {0};
	
	init_display(&display);
	while (display.quit == false)
	{
		if (display.state == MENU)
			menu_handler(&display);
		else if (display.state == GAME)
			game_handler(&display);
		else if (display.state == ENDGAME)
			endgame_handler(&display);
	}
	save_score(display.board.max_score);
	endwin();
}


void	menu_handler(t_display *display)
{
	int	input = 0;

	resize_menu(display);
	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
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
				game_init(&display->board, display->board.size);
				return ;
			}
			else if (display->option_selected == QUIT_OPTION)
			{
				display->quit = true;
				return ;
			}
		}
	}
	display->quit = true;
	return ;
}

void	game_handler(t_display *display)
{
	int	input = 0;

	resize_board(display);
	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
			resize_board(display);
		else if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT)
		{
			game_loop(&display->board, input);
			display_board(display);
			if (display->board.game_status != RUNNING && display->board.game_status != ENDLESS)
			{
				display->state = ENDGAME;
				display->option_selected = STARTOVER_OPTION;
				return ;
			}
		}
	}
	display->state = MENU;
	return ;
}


void	endgame_handler(t_display *display)
{
	int	input = 0;

	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
			resize_choice(display);
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
				game_init(&display->board, display->board.size);
				display->state = GAME;
				return ;
			}
			if (display->option_selected == CONTINUE_OPTION)
			{
				display->board.game_status = ENDLESS;
				display->state = GAME;
				return ;
			}
			if (display->option_selected == QUITGAME_OPTION)
			{
				display->state = MENU;
				display->option_selected = PLAY_OPTION;
				return ;
			}
		}
	}
	display->state = MENU;
	return ;
}


test main:

display
init tout
tant que display-> quit est a false
	je regarde le current state
	si le current state est menu, j'appelle la fonction de menu
	si le current state est le game, j'appelle la fonction de game

fonction de menu:
tant que l'input est pas escape ou que menu-> quit a pas ete presse:
	je modifie les parametres du game en fonction du bouton presse
	si play a ete presse, je change le state du display et je return
je mets le display -> quit a true et je return

fonction de game:
tant que l'input est pas escape:
tant que game->over est pas a true:
	je joue au jeu et je display le board
si game->over est a true, je regarde si le joueur a gagné ou perdu, et en fonction je display un message pour savoir si continue a jouer
si oui, je mets game->over a false et je continue la boucle (si perdu, je remets le score a 0 et je créé un nouveau board)
je mets le display-> state au menu et je return
*/
