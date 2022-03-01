SRC =	color.c					\
		ft_atof.c				\
		ft_atosign.c			\
		key_hook.c				\
		mlx.c					\
		mouse_hook.c			\
		parsing.c				\
		mandelbrot.c			\
		julia.c					\
		burning_ship_bonus.c	\
		fractals.c				\
		main.c	

OBJ = $(SRC:.c=.o)

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

NAME = fractol

CC = gcc

$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) $(CLFAGS) $(MLXFLAGS) -o $(NAME)

%.o: %.c fractol.h
	$(CC) $(CFLAGS) -Imlx -c -Ofast -O -O1 -O2 -O3 $< -o $@

clean:
	make -C mlx clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY:	all bonus clean fclean re
