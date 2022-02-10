/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:37:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 13:45:51 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	put_color(t_root *root, int x, int y, int i)
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

void	put_plot(t_root *root, int x, int y)
{
	long double	real;
	long double	imaginary;

	real = x * root->r_screen.x_scale + root->r_screen.x_offset;
	imaginary = y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (real == 0 || imaginary == 0)
		my_pxl_put(root, x, y, 0x0FFFFFF);
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
		if (root->set == 1)
			mandelbrot(root, x, y);
		else if (root->set == 2)
			julia(root, x, y);
		while (x < WIDTH)
		{
			if (root->set == 1)
				mandelbrot(root, x, y);
			else if (root->set == 2)
				julia(root, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	refresh(root);
}
