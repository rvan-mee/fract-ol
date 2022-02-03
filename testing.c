/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:14:44 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/03 17:36:47 by rvan-mee      ########   odam.nl         */
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
#define ESC 53
#define OFFSET 0.5
#define ZOOM 3

void	my_pxl_put(r_root *root, int x, int y, int color)
{
	char	*dst;

	dst = root->r_data.addr + (y * root->r_data.ll + x * (root->r_data.bpp / 8));
	*(unsigned int*)dst = color;
}

void put_color(r_root *root, int x, int y, int iteri)
{
	int color;
	
	if (iteri < (root->r_screen.iteri / 3) * 1)
	{
		color = iteri * 256;
		my_pxl_put(root, x, y, color);
	}
	else if (iteri < (root->r_screen.iteri / 3) * 2)
	{
		color = iteri * 64 * 256;
		my_pxl_put(root, x, y, color);
	}
	else if (iteri > (root->r_screen.iteri / 3) * 2)
	{
		color = iteri * 64 * 256 * 256;
		my_pxl_put(root, x, y, color);
	}
}

int	mandelbrot(r_root *root, double x, double y)
{
	double	real = 0;
	double	imaginary = 0;
	double	real_tmp;
	double	real_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
	double	imaginary_start = y * root->r_screen.y_scale + root->r_screen.y_offset;
	int		i = 0;
//	int		color = root->r_screen.color;
	
	while (i <= root->r_screen.iteri)
	{
		real_tmp = real;
		real = real * real - imaginary * imaginary + real_start;
		imaginary = real_tmp * imaginary * 2 + imaginary_start;
		if (real * real + imaginary * imaginary >= 4)
			break ;
		i++;
	}
	if (i == root->r_screen.iteri + 1)
		my_pxl_put(root, x, y, 0x0000000);
	else
		put_color(root, x, y, i);
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
		mandelbrot(root, x, y);
		while (x < WIDTH)
		{
			mandelbrot(root, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	refresh(root);
}

int	key_hook(int keycode, r_root *root)
{
	if (keycode == ESC)
		exit(1);
	else if (keycode == ARROW_DOWN)
		root->r_screen.y_offset -= OFFSET;
	else if (keycode == ARROW_UP)
		root->r_screen.y_offset += OFFSET;
	else if (keycode == ARROW_LEFT)
		root->r_screen.x_offset -= OFFSET;
	else if (keycode == ARROW_RIGHT)
		root->r_screen.x_offset += OFFSET;
	if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT || 
		keycode == ARROW_DOWN || keycode == ARROW_UP)
		color_change(root);
	//printf("keycode = %d -- color= %x\n", keycode, root->r_screen.color);
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
		root->r_screen.y_scale /= ZOOM;
		root->r_screen.x_scale /= ZOOM;
		root->r_screen.x_offset /= ZOOM;
		root->r_screen.y_offset /= ZOOM;
	}
	else if (button == MOUSE_DOWN)
	{
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
	root->r_screen.iteri = 500;
	root->r_screen.x_scale = 3 / (double)WIDTH;
	root->r_screen.y_scale = 2 / (double)HEIGHT * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 1;
	root->r_screen.color = 0x00FF000F;
	root->mlx_win = mlx_new_window(root->mlx, WIDTH, HEIGHT, "testing!");
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	root->r_data.addr = mlx_get_data_addr(root->r_data.img, &root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	color_change(root);
	return (0);
}

int	main(void)
{
	struct s_root	root;

	init_mlx(&root);
	mlx_key_hook(root.mlx_win, key_hook, &root);
	mlx_mouse_hook(root.mlx_win, mouse_hook, &root);
	mlx_loop(root.mlx);
}

//man /usr/share/man/man1/