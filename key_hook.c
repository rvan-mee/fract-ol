/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:17:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/11 18:58:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	single_color_change(t_root *root)
{
	static int	i;

	if (i > 10)
		i = 0;
	root->r_screen.color = root->r_screen.all_options[i];
	i++;
}

void	set_color_change_type(int key, t_root *root)
{
	if (key == KEY_R)
	{
		root->r_screen.color_type = 0;
		if (root->r_screen.color > 0 && root->r_screen.color < 0x000FFFFFF)
			root->r_screen.color += 1;
		else
			root->r_screen.color -= 255*255;
		return ;
	}
	root->r_screen.color_type = 1;
	single_color_change(root);
}

void	set_zoom(int key, t_root *root)
{
	if (key == PAGE_UP)
	{
		root->r_screen.iteri += 50;
		return ;
	}
	if (root->r_screen.iteri > 100)
		root->r_screen.iteri -= 50;
}
long double	set_zoom_offset(t_root *root)
{
	long double	zoom_offset;

	zoom_offset = 0;
	if (root->r_screen.zoom <= 3)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 100;
	else if (root->r_screen.zoom >= 3.5 && root->r_screen.zoom <= 4.5)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 250;
	else if (root->r_screen.zoom >= 5 && root->r_screen.zoom <= 6.5)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 5000;
	else if (root->r_screen.zoom >= 7 && root->r_screen.zoom <= 8.5)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 50000;
	else if (root->r_screen.zoom >= 9 && root->r_screen.zoom <= 11)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 3000000;
	else if (root->r_screen.zoom >= 11.5)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 250000000;
	return (zoom_offset);
}
int	key_hook(int key, t_root *root)
{
	printf("key: %d\n", key);
	printf("zoom: %Lf\noffset: %Lf\n", root->r_screen.zoom, (long double)OFFSET);
	printf("offset x: %Lf\noffset y: %Lf\n\n", root->r_screen.x_offset, root->r_screen.y_offset);
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
	else if (key == KEY_C || key == KEY_R)
		set_color_change_type(key, root);
	else if (key == PAGE_UP || key == PAGE_DOWN)
		set_zoom(key, root);
	if (key == ARW_RIGHT || key == ARW_LEFT || key == ARW_DOWN || key == KEY_R
		|| key == ARW_UP || key == KEY_C || key == PAGE_DOWN || key == PAGE_UP)
		color_change(root);
	printf("AFTER:\noffset x: %Lf\noffset y: %Lf\n\n\n", root->r_screen.x_offset, root->r_screen.y_offset);
	return (0);
}
