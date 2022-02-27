SRC =	color.c			\
		ft_atof.c		\
		ft_atosign.c	\
		key_hook.c		\
		mlx.c			\
		mouse_hook.c	\
		parsing.c		\
		mandelbrot.c	\
		julia.c			\
		burning_ship.c	\
		fractals.c		\
		main.c			

OBJ = $(SRC:.c=.o)

NAME = fractol

all: $(NAME)

clean:
	make -C mlx clean
	rm *.o

fclean: clean
	make -C mlx fclean
	rm -f $(NAME)

%.o: %.c fractol.h
	$(CC) -Wall -Wextra -Werror -Imlx -fsanitize=address -g -c -Ofast -O -O1 -O2 -O3 $< -o $@

$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) -fsanitize=address -g -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

re: fclean all

CC = gcc

.PHONY:	all bonus clean fclean re