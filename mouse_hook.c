/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_hook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:10:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/25 13:45:10 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// zooms in by making the values smaller with
// a set amount of (ZOOM) defined in the headerfile.
void	mouse_up(t_root *root)
{
	root->r_screen.zoom += 1;
	root->r_screen.y_scale /= ZOOM;
	root->r_screen.x_scale /= ZOOM;
	root->r_screen.x_offset /= ZOOM;
	root->r_screen.y_offset /= ZOOM;
}

// zooms out by making the values bigger with
// a set amount of (ZOOM) defined in the headerfile.
void	mouse_down(t_root *root)
{
	root->r_screen.zoom -= 1;
	root->r_screen.y_scale *= ZOOM;
	root->r_screen.x_scale *= ZOOM;
	root->r_screen.x_offset *= ZOOM;
	root->r_screen.y_offset *= ZOOM;
}

// If a mouse button is used this function gets called.
// Depending on the (int button) value we know what button was used.
// MLX gives the x and y value of the position of the mouse 
// at the time of button press.
// Examples of mouse buttons: Scroll up and Scroll down.
int	mouse_hook(int button, int x, int y, t_root *root)
{
	long double	x_start;
	long double	y_start;
	long double	x_new;
	long double	y_new;

	x_start = (long double)x * root->r_screen.x_scale + root->r_screen.x_offset;
	y_start = (long double)y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (button == MOUSE_UP)
		mouse_up(root);
	else if (button == MOUSE_DOWN)
		mouse_down(root);
	if (button == MOUSE_UP || button == MOUSE_DOWN)
	{
		x_new = (long double)x * root->r_screen.x_scale
			+ root->r_screen.x_offset;
		y_new = (long double)y * root->r_screen.y_scale
			+ root->r_screen.y_offset;
		x_new -= x_start;
		y_new -= y_start;
		root->r_screen.x_offset -= x_new;
		root->r_screen.y_offset -= y_new;
		color_change(root);
	}
	return (0);
}
