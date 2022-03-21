/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:17:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/03/21 11:34:48 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Cycles through the colors initiated in the function init_colors (main.c).
void	single_color_change(t_root *root)
{
	static int	i;

	if (i > 5)
		i = 0;
	root->r_screen.all_options = i;
	i++;
}

// Checks what kind of color mode has to be used depending on what key is used 
// (rainbow or single).
// If pressed again will changed the current colors 
// apearing on screen in the selected mode.
void	set_color_change_type(int key, t_root *root)
{
	static int	i;

	if (key == KEY_R)
	{
		if (i > 10)
			i = 0;
		root->r_screen.color_type = 0;
		root->r_screen.color = root->r_screen.rainbow_base[i];
		i++;
	}
	else if (key == KEY_C)
	{
		root->r_screen.color_type = 1;
		single_color_change(root);
	}
	else
		root->r_screen.color_type = 2;
}

// If page up or page down is used changes the iterations to be higher or lower.
void	set_iteri(int key, t_root *root)
{
	if (key == PAGE_UP)
	{
		root->r_screen.iteri += 50;
		return ;
	}
	if (root->r_screen.iteri > 100)
		root->r_screen.iteri -= 50;
}

// Sets the offset of the arrow keys to be more user friendly depending 
// on the depth of the current zoom.
long double	set_zoom_offset(t_root *root)
{
	long double	zoom_offset;

	zoom_offset = 1;
	if (root->r_screen.zoom <= 6 && root->r_screen.zoom != 0)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 50;
	else if (root->r_screen.zoom >= 7 && root->r_screen.zoom <= 9)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 125;
	else if (root->r_screen.zoom >= 10 && root->r_screen.zoom <= 13)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 5000;
	else if (root->r_screen.zoom >= 14 && root->r_screen.zoom <= 17)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 50000;
	else if (root->r_screen.zoom >= 18 && root->r_screen.zoom <= 22)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 3000000;
	else if (root->r_screen.zoom >= 23)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 250000000;
	return (zoom_offset);
}

// Function gets called whenever a key press is done within runtime.
// Checks what kind of key is used with the given (int key) value and
// calls the assigned function or adjusts a certain value.
// Examples of keys that can be used: page up & down, arrow keys, C and R.
int	key_hook(int key, t_root *root)
{
	if (key == ESC)
		exit(1);
	else if (key == ARW_DOWN)
		root->r_screen.y_offset -= (long double)OFFSET / set_zoom_offset(root);
	else if (key == ARW_UP)
		root->r_screen.y_offset += (long double)OFFSET / set_zoom_offset(root);
	else if (key == ARW_LEFT)
		root->r_screen.x_offset -= (long double)OFFSET / set_zoom_offset(root);
	else if (key == ARW_RIGHT)
		root->r_screen.x_offset += (long double)OFFSET / set_zoom_offset(root);
	else if (key == KEY_C || key == KEY_R || key == KEY_B)
		set_color_change_type(key, root);
	else if (key == PAGE_UP || key == PAGE_DOWN)
		set_iteri(key, root);
	if (key == ARW_RIGHT || key == ARW_LEFT || key == ARW_DOWN || key == KEY_R
		|| key == ARW_UP || key == KEY_C || key == PAGE_DOWN || key == PAGE_UP
		|| key == KEY_B)
		color_change(root);
	return (0);
}
