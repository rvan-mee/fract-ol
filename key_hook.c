/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:17:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 13:46:03 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_root *root)
{
	if (key == ESC)
		exit(1);
	else if (key == ARROW_DOWN)
		root->r_screen.y_offset -= (long double)OFFSET - root->r_screen.zoom;
	else if (key == ARROW_UP)
		root->r_screen.y_offset += (long double)OFFSET + root->r_screen.zoom;
	else if (key == ARROW_LEFT)
		root->r_screen.x_offset -= (long double)OFFSET - root->r_screen.zoom;
	else if (key == ARROW_RIGHT)
		root->r_screen.x_offset += (long double)OFFSET + root->r_screen.zoom;
	else if (key == KEY_C)
	{
		if (root->r_screen.color > 0 && root->r_screen.color < 0x000FFFFFF)
			root->r_screen.color += 1;
		else if (root->r_screen.color == 0x000FFFFFF)
			root->r_screen.color -= 255 * 255;
	}
	else if (key == PAGE_UP)
		root->r_screen.iteri += 50;
	else if (key == PAGE_DOWN)
		root->r_screen.iteri -= 50;
	if (key == ARROW_RIGHT || key == ARROW_LEFT || key == ARROW_DOWN
		|| key == ARROW_UP || key == KEY_C || key == PAGE_DOWN || key == PAGE_UP)
		color_change(root);
	return (0);
}
