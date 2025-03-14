# HOW TO USE
# $ make
# $ ./chess_game
# blah blah it plays --> end
# $ make clean 
# make clean removes all created .o files

# ADDED FOR SDL.C BUT ERROR BECAUSE OF TWO MAIN()
# IF U WANT TO JUST GAME --> Makefile from release version

NAME = chess_game
CC = gcc

CFLAGS = -Wall -g  $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)
SRCS = 	get_input.c \
		init_board.c \
		print_board.c \
		validate_moves.c \
		play.c \
		make_move.c \
		calculate_attack.c \
#		SDL.c
		


# maybe get special headers for all functions?
HEADERS = general_structures.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
