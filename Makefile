#---------------- VARIABLES ----------------#

NAME=2048
CC=cc
CFLAGS=-Wall -Werror -Wextra -I $(INCLUDE_DIR)
LDFLAGS=-lncurses
DEPS=-MMD -MP

#---------------- DIRECTORIES ----------------#

INCLUDE_DIR = includes/
SCR_DIR = srcs/
OBJ_DIR = .build/

#---------------- SOURCE FILES ----------------#

C_FILES = $(SCR_DIR)testmain.c \
		  $(SCR_DIR)display.c \
		  $(SCR_DIR)get_next_line.c \
		  $(SCR_DIR)game_init.c \
		  $(SCR_DIR)game_loop.c \
		  $(SCR_DIR)tile_gen.c \
		  $(SCR_DIR)init.c

HEADERS = $(INCLUDE_DIR)wkw.h \
		  $(INCLUDE_DIR)colors.h \
		  $(INCLUDE_DIR)get_next_line.h

#---------------- OBJECTS ----------------#

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(C_FILES))
DEPENDENCIES = $(OBJS:.o=.d)

#---------------- RULES ----------------#

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPS) -c $< -o $@

clean:
	rm -fr $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPENDENCIES)

.PHONY: all clean fclean re
