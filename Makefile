SRC =	testing.c

OBJ = $(SRC:.c=.o)

NAME = fract-ol

all: $(NAME)

clean:
	rm *.o

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

CC = gcc