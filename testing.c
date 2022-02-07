/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:14:44 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/07 16:17:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#define WIDTH 1920   //2880
#define HEIGHT 1080  //1495
#define FAIL 0
#define SUCCESS 1
#define MOUSE_DOWN 5
#define MOUSE_UP 4
#define ARROW_UP 126
#define ARROW_LEFT 123
#define ARROW_DOWN 125
#define ARROW_RIGHT 124
#define	PAGE_UP 116
#define PAGE_DOWN 121
#define KEY_C 8
#define ESC 53
#define OFFSET 1
#define ZOOM 3


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n)
	{
		if ((str1[i] == 0) || (str2[i] == 0) || (str1[i] != str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	my_pxl_put(r_root *root, int x, int y, int color)
{
	char	*dst;

	dst = root->r_data.addr + (y * root->r_data.ll + x * (root->r_data.bpp / 8));
	*(unsigned int*)dst = color;
}

int color(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void put_color(r_root *root, int x, int y, int i)
{
	if (i == root->r_screen.iteri + 1)
	{
		my_pxl_put(root, x, y, 0);
		return ;
	}
	if (i < (root->r_screen.iteri / 3) * 1)
	{
		while (i < 25)
			i++;
		my_pxl_put(root, x, y, color(i * 2, i * root->r_screen.color, i / 2));
	}
	else if (i < (root->r_screen.iteri / 3) * 2)
	{
		my_pxl_put(root, x, y, color(i * 2, i * 2, i * root->r_screen.color));
	}
	else if (i > (root->r_screen.iteri / 3) * 2)
	{
		my_pxl_put(root, x, y, color(i * root->r_screen.color, i, i / 2));
	}
}

void	put_plot(r_root *root, int x, int y)
{
	double	real;
	double	imaginary;

	real = x * root->r_screen.x_scale + root->r_screen.x_offset;
	imaginary = y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (real == 0 || imaginary == 0)
		my_pxl_put(root, x, y, 0x0FFFFFF);
}

int	mandelbrot(r_root *root, double x, double y)
{
	int		i;
	double	real;
	double	imaginary;
	double	real_tmp;
	double	real_start;
	double	imaginary_start;

	i = 0;
	real = 0;
	imaginary = 0;
	real_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
	imaginary_start = y * root->r_screen.y_scale + root->r_screen.y_offset;
	while (real * real + imaginary * imaginary <= 2 * 2 && i <= root->r_screen.iteri)
	{
		real_tmp = real * real - imaginary * imaginary + real_start;
		imaginary = 2 * real * imaginary + imaginary_start;
		real = real_tmp;
		i++;
	}
	put_color(root, x, y, i);
	put_plot(root, x, y);
	return (SUCCESS);
}

int julia(r_root *root, double x, double y)
{
	int		i;
	double	new_x;
	double	new_y;
	double	x_temp;

	i = 0;
	new_x = x * root->r_screen.x_scale + root->r_screen.x_offset;
	new_y = y * root->r_screen.y_scale + root->r_screen.y_offset;
	while (new_x * new_x + new_y * new_y < 2 * 2 && i <= root->r_screen.iteri)
	{
		x_temp = new_x * new_x - new_y * new_y;
		new_y = 2 * new_x * new_y + root->r_julia.y;
		new_x = x_temp + root->r_julia.x;
		i++;
	}
	put_color(root, x, y, i);
	// put_plot(root, x, y);
	return (SUCCESS);
}

void refresh(r_root *root)
{
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->r_data.img, 0 + root->r_screen.x_scale, 0 + root->r_screen.y_scale);
}

void new_img(r_root *root)
{
	mlx_destroy_image(root->mlx, root->r_data.img);
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->r_data.img, 0, 0);
}

void color_change(r_root *root)
{
	int	x = 0;
	int	y = 0;

	new_img(root);
	while (y < HEIGHT)
	{
		if (root->set == 1)
			mandelbrot(root, x, y);
		else
			julia(root, x, y);
		while (x < WIDTH)
		{
			if (root->set == 1)
				mandelbrot(root, x, y);
			else
				julia(root, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	refresh(root);
}

int	key_hook(int keycode, r_root *root)
{
	printf("keycode == %d\n", keycode);
	if (keycode == ESC)
		exit(1);
	else if (keycode == ARROW_DOWN)
		root->r_screen.y_offset -= (double)OFFSET - root->r_screen.zoom;
	else if (keycode == ARROW_UP)
		root->r_screen.y_offset += (double)OFFSET + root->r_screen.zoom;
	else if (keycode == ARROW_LEFT)
		root->r_screen.x_offset -= (double)OFFSET - root->r_screen.zoom;
	else if (keycode == ARROW_RIGHT)
		root->r_screen.x_offset += (double)OFFSET + root->r_screen.zoom;
	else if (keycode == KEY_C)
	{
		if (root->r_screen.color > 0 && root->r_screen.color < 0x000FFFFFF)
			root->r_screen.color += 1;
		else if (root->r_screen.color == 0x000FFFFFF)
			root->r_screen.color -= 255*255;
		printf("color = %d\n", root->r_screen.color);
	}
	else if (keycode == PAGE_UP)
		root->r_screen.iteri += 50;
	else if (keycode == PAGE_DOWN)
		root->r_screen.iteri -= 50;
	if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT || 
		keycode == ARROW_DOWN || keycode == ARROW_UP || keycode == KEY_C ||
		keycode == PAGE_DOWN || keycode == PAGE_UP)
		color_change(root);
	return (0);
}
int	mouse_hook(int button, int x, int y, r_root *root)
{
	double	x_start = (double)x * root->r_screen.x_scale + root->r_screen.x_offset;
	double	y_start = (double)y * root->r_screen.y_scale + root->r_screen.y_offset;
	double	x_new;
	double	y_new;

	if (button == MOUSE_UP)
	{
		root->r_screen.zoom += 0.5;
		root->r_screen.y_scale /= ZOOM;
		root->r_screen.x_scale /= ZOOM;
		root->r_screen.x_offset /= ZOOM;
		root->r_screen.y_offset /= ZOOM;
	}
	else if (button == MOUSE_DOWN)
	{
		if (root->r_screen.zoom > 1)
			root->r_screen.zoom -= 0.5;
		root->r_screen.y_scale *= ZOOM;
		root->r_screen.x_scale *= ZOOM;
		root->r_screen.x_offset *= ZOOM;
		root->r_screen.y_offset *= ZOOM;
	}
	if (button == MOUSE_UP || button == MOUSE_DOWN)
	{
		x_new = (double)x * root->r_screen.x_scale + root->r_screen.x_offset;
		y_new = (double)y * root->r_screen.y_scale + root->r_screen.y_offset;
		x_new -= x_start;
		y_new -= y_start;
		root->r_screen.x_offset -= x_new;
		root->r_screen.y_offset	-= y_new;
		color_change(root);
	}
	return (0);
}

int	init_mlx(r_root *root)
{
	root->mlx = mlx_init();
	root->r_screen.iteri = 50;
	root->r_screen.x_scale = 3 / (double)WIDTH;
	root->r_screen.y_scale = 2 / (double)HEIGHT * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 1;
	root->r_screen.color = 0x0000000F;
	root->mlx_win = mlx_new_window(root->mlx, WIDTH, HEIGHT, "testing!");
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	root->r_data.addr = mlx_get_data_addr(root->r_data.img, &root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	color_change(root);
	return (0);
}

void check_input(int argc, char **argv, r_root *root)
{
	if (argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 10)))
		root->set = 1;
	else if (argc == 2 && !(ft_strncmp(argv[1], "julia", 5)))
	{
		write(1, "Please use a valid c\nTry this: 0.285 + 0.01i\n", 42);
		exit(1);
	}
	else if (argc == 3 && !(ft_strncmp(argv[1], "julia", 5)))
	{
		root->set = 2;
		root->r_julia.x = 0;
		root->r_julia.y = ft_atof(argv[argc - 1]);
	}
	else if (argc == 4 && !(ft_strncmp(argv[1], "julia", 5)))
	{
		root->set = 2;
		root->r_julia.x = ft_atof(argv[argc - 2]);
		root->r_julia.y = ft_atof(argv[argc - 1]);
	}
	else
	{
		write(1, "Please use a valid argument\nmandelbrot\njulia\n", 46);
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	struct s_root	root;

	check_input(argc, argv, &root);
	init_mlx(&root);
	mlx_key_hook(root.mlx_win, key_hook, &root);
	mlx_mouse_hook(root.mlx_win, mouse_hook, &root);
	mlx_loop(root.mlx);
	return (0);
}

//man /usr/share/man/man1/