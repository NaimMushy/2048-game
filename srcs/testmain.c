#include "wkw.h"

int	test_main(void)
{
	t_display	display = {0};
	
	init_display();
	while (display->quit == false)
	{
		if (display_state == MENU)
			menu_handler(&display);
		else if (display_state == GAME)
			game_handler(&display);
	}
	endwin();
}


void	menu_handler(t_display *display)
{
	int	input = 0;

	while (!display_menu(display))
		// print TOO_SMALL_MSG
	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_DOWN || input == KEY_UP)
			// modifier parametre pointé
		if (input == SPACE)
			// regarder paramètre pointé
			// si c'est quitter, mettre le display->quit a true
			// si c'est play, mettre le display->state à GAME et reutrn
		if (input == KEY_RESIZE)
		{
			while (!display_menu(display))
				// print TOO_SMALL_MSG
		}
	}
	display->quit = true;
	return ;
}


void	game_handler(t_display *display)
{
	int	input = 0;

	while (!display_game(display))
		// print TOO_SMALL_MSG
	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
		{
			while (!display_game(display))
				// print TOO_SMALL_MSG
		}
		game_move = game_function(input);
		if (game_move != 0)
			display_game(display);
		if (game->over)
		{
			display->state = CHOICE;
			return ;
		}
	}
	display->state = MENU;
	return ;
}


void	choice_handler(t_display *display)
{
	int	input = 0;

	while (!display_choice(display))
		// print TOO_SMALL_MSG
	while ((input = wgetch(stdscr)) != ESCAPE_KEY)
	{
		if (input == KEY_RESIZE)
		{
			while (!display_choice(display))
				// print TOO_SMALL_MSG
		}
		if (input == KEY_UP || input == KEY_DOWN)
			// modifie le parametre pointé
		if (input == ENTER)
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


/*
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


int	main(void)
{
	int		input = 0;
	t_display	game_display = {0};
	int	board1[MAX_SIZE][MAX_SIZE] = {{2, 0, 4, 8}, {0, 0, 16, 8}, {16, 0, 32, 64}, {2, 2, 16, 4}};
	int	board2[MAX_SIZE][MAX_SIZE] = {{2, 8, 4, 128}, {2, 0, 16, 2}, {16, 0, 0, 64}, {2, 64, 16, 4}};
	int cur_board = 2;

	init_display();
	game_display.player_score = 0;
	game_display.best_score = 4096;
	game_display.board_sz = 4;
	change_board(&game_display, board1);
	for (int i = 0; i < FILENAME_LEN; i++)
		game_display.letter_filename[i] = FILENAME[i];
	while (!resize_window(&game_display))
		mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
	while ((input = wgetch(stdscr)) != 27)
	{
		if (input == KEY_RESIZE)
		{
			handle_resize();
			if (!resize_window(&game_display))
				mvwaddstr(stdscr, (LINES - 1) / 2, (COLS - strlen(TOO_SMALL_MSG)) / 2, TOO_SMALL_MSG);
		}
		if (input == 110)
		{
			if (cur_board == 1)
			{
				change_board(&game_display, board1);
				cur_board = 2;
			}
			else
			{
				change_board(&game_display, board2);
				cur_board = 1;
			}
			display_board(&game_display);
		}
	}
	endwin();
	return (1);
}
