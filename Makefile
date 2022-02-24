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
	rm *.o
	rm fractol

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c -Ofast -O -O1 -O2 -O3 $< -o $@

$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

re: clean all
	
CC = gcc