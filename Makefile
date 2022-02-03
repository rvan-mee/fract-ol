SRC =	testing.c

OBJ = $(SRC:.c=.o)

NAME = fract-ol

all: $(NAME)

clean:
	rm *.o

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c -O -O1 -O2 -O3 $< -o $@

$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

re: clean all
	
CC = gcc