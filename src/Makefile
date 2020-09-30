##
## ETNA PROJECT, 02/05/2019 by soubri_j
## Makeflile
## File description: 
##      Makefile for Bomberman.
##
CFLAGS				= -Wall -Wextra -Werror

LINKER_FLAGS		= $(shell pkg-config --libs sdl2)

CC					= gcc

RM					= rm -f

PROGRAM_NAME		= bomberman

SRC					= $(shell ls *.c)

OBJ					= $(SRC:.c=.o)

all: $(PROGRAM_NAME)
	
$(PROGRAM_NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKER_FLAGS) -o $(PROGRAM_NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(PROGRAM_NAME)

re: fclean all

.PHONY: all $(PROGRAM_NAME) clean fclean re