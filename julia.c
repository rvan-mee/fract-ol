/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:34:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/11 14:58:00 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_root *root, long double x, long double y)
{
	int			i;
	long double	new_x;
	long double	new_y;
	long double	x_temp;

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
	put_single_color(root, x, y, i);
	return (SUCCESS);
}
