/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:34:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 13:46:06 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_helper(t_root *r, int *i, long double i_s, long double r_s)
{
	long double	rl;
	long double	im;
	long double	rl_tmp;

	rl = 0;
	im = 0;
	while (rl * rl + im * im <= 2 * 2 && *i <= r->r_screen.iteri)
	{
		rl_tmp = rl * rl - im * im + r_s;
		im = 2 * rl * im + i_s;
		rl = rl_tmp;
		*i += 1;
	}
}

int	mandelbrot(t_root *root, long double x, long double y)
{
	int			i;
	long double	r_start;
	long double	i_start;

	i = 0;
	r_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
	i_start = y * root->r_screen.y_scale + root->r_screen.y_offset;
	mandelbrot_helper(root, &i, i_start, r_start);
	put_color(root, x, y, i);
	put_plot(root, x, y);
	return (SUCCESS);
}
