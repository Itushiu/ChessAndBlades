NAME = chess_game
CC = gcc
# -DUSE_SDL flag is for SDL, check later if needed
CFLAGS = -Wall -Wextra -std=c99 #-DUSE_SDL

SRCS = 	main.c \
		get_input.c \
		init_board.c \
		print_board.c \
		validate_moves.c 
		
		
		
# make_move.c 
# play.c

# maybe get special headers for all functions?
HEADERS = general_structures.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
