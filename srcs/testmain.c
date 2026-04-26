#include "wkw.h"

void	game_handler(t_display *display);

int	main(void)
{
	t_display	display = {0};
	
	init_display(&display);
	display.state = GAME;
	display.quit = false;
	game_init(&display.board, DEFAULT_SIZE);
	while (display.quit == false)
	{
		if (display.state == GAME)
			game_handler(&display);
	}
	endwin();
}


/*
void	menu_handler(t_display *display)
{
	int	input = 0;

	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
			resize_menu(display);
		else if (input == KEY_DOWN || input == KEY_UP)
			// modifier parametre pointé
		else if (input == SPACE)
			// regarder paramètre pointé
			// si c'est quitter, mettre le display->quit a true
			// si c'est play, mettre le display->state à GAME et reutrn
	}
	display->quit = true;
	return ;
}
*/

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
				display->state = CHOICE;
				return ;
			}
		}
	}
	display->quit = true;
	return ;
}


/*
void	choice_handler(t_display *display)
{
	int	input = 0;

	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
			resize_choice(display);
		else if (input == KEY_UP || input == KEY_DOWN)
			// modifie le parametre pointé
		else if (input == ENTER)
		{
			// regarde le paramètre pointé
			// si c'est oui, mettre le display state a game
			// sinon mettre le display a menu
			// modifier les paramètres du jeu en fonction resultat: si perdu, mettre a zero et creer un nouveau board
			// return
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
