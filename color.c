/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:37:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/11 15:23:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	put_rainbow(t_root *root, int x, int y, int i)
{
	int	new_color;

	new_color = 0;
	if (i == root->r_screen.iteri + 1)
	{
		my_pxl_put(root, x, y, 0);
		return ;
	}
	if (i < (root->r_screen.iteri / 3) * 1)
		new_color += color(i * 2, i * root->r_screen.color, i / 2);
	else if (i < (root->r_screen.iteri / 3) * 2)
		new_color += color(i * 2, i * 2, i * root->r_screen.color);
	else if (i > (root->r_screen.iteri / 3) * 2)
		new_color += color(i * root->r_screen.color, i, i / 2);
	if (new_color < 40)
		new_color += 0x000F00F0;
	my_pxl_put(root, x, y, new_color);
}

void	put_single_color(t_root *root, int x, int y, int i)
{
	int new_color;

	new_color = 0;
	if (i == root->r_screen.iteri + 1)
		my_pxl_put(root, x, y, 0);
	else
	{
		new_color = i * 64 + root->r_screen.color;
		if (new_color < 0x0000000FF)
			new_color = 0x0FFFFFFFF;
		my_pxl_put(root, x, y, new_color);
	}
}

void	fractal(int type, int x, int y, t_root *root)
{
	if (type == 1)
		mandelbrot(root, x, y);
	else if (type == 2)
		julia(root, x, y);
	else if (type == 3)
		burning_ship(root, x, y);
}

void	color_change(t_root *root)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	new_img(root);
	while (y < HEIGHT)
	{
		fractal(root->set, x, y, root);
		while (x < WIDTH)
		{
			fractal(root->set, x, y, root);
			x++;
		}
		x = 0;
		y++;
	}
	refresh(root);
}
