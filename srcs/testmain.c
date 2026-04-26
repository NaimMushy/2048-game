#include "wkw.h"


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
