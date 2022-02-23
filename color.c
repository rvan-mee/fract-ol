/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:37:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/23 14:23:56 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Returns a color's RGB value based on the input R G and B.
// Max values should be 256 per color.
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

// Depending on the Iterations vs Max Iterations sets the color to black
// or a color thats based off the current selected color (change by pressing C).
void	put_single_color(t_root *root, int x, int y, int i)
{
	int	new_color;

	new_color = 0;
	if (i == root->r_screen.iteri + 1)
		my_pxl_put(root, x, y, 0);
	else
	{
		new_color = i * 64 + root->r_screen.color;
		if (new_color < 0x0000000FF)
			new_color = root->r_screen.color;
		my_pxl_put(root, x, y, new_color);
	}
}
