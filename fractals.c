/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractals.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 13:53:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/24 18:57:02 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Applies the correct funtion to the pixel given the command line input.
void	fractal(int type, int x, int y, t_root *root)
{
	if (type == 1)
		mandelbrot(root, x, y);
	else if (type == 2)
		julia(root, x, y);
	else if (type == 3)
		burning_ship(root, x, y);
}

// Loops through all the possible pixels given the set 
// (HEIGHT) and (WIDTH) defined in the headerfile.
void	color_change(t_root *root)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	new_img(root);
	while (y <= HEIGHT)
	{
		fractal(root->set, x, y, root);
		while (x <= WIDTH)
		{
			fractal(root->set, x, y, root);
			x++;
		}
		x = 0;
		y++;
	}
	refresh(root);
}
