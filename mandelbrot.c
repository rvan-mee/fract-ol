/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:34:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 12:35:33 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	mandelbrot(r_root *root, long double x, long double y)
{
	int			i;
	long double	real;
	long double	imaginary;
	long double	real_tmp;
	long double	real_start;
	long double	imaginary_start;

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
