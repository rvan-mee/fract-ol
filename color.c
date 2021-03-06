/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:37:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/25 13:26:53 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Returns a color's RGB value based on the input R G and B.
// Max values should be 255 per color.
int	color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// Depending on the Iterations vs Max Iterations sets the color to black
// or sets the color to change in a much more rapid way then the single 
// version of this function.
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

// Scales from black to white.
// (pei) is the % of the current iteration compared to
// the max iteration, scaled to 255.
void	put_black_to_white(t_root *root, int x, int y, int i)
{
	double	pei;

	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
	{
		my_pxl_put(root, x, y, 0x00FFFFFF);
		return ;
	}
	my_pxl_put(root, x, y, color(pei, pei, pei));
}

// Depending on the Iterations vs Max Iterations sets the color to black
// or a color thats based off the current selected color (change by pressing C).
void	put_single_color(t_root *root, int x, int y, int i)
{
	int			j;
	double		pei;

	j = root->r_screen.all_options;
	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
		my_pxl_put(root, x, y, 0);
	else
	{
		my_pxl_put(root, x, y,
			color(root->r_screen.options[j][0] * pei,
				root->r_screen.options[j][1] * pei,
				root->r_screen.options[j][2] * pei));
	}
}
