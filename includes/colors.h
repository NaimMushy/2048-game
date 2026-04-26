#ifndef COLORS_H
# define COLORS_H


# define RGB_TO_CURSES(x) ((int)((float)x * 3.90625))
# define NB_COLORS 11
# define START_COLOR 8


enum	e_colors
{
	RED1 = START_COLOR,
	ORANGE,
	YELLOW1,
	GREEN1,
	BLUE1,
	PURPLE1,
	RED2,
	GREEN2,
	BLUE2,
	PURPLE2,
	PINK
};

#endif
