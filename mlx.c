/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:05:19 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/23 13:23:19 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Sets a specific pixel to a color with the given value (int color)
void	my_pxl_put(t_root *root, int x, int y, int color)
{
	char	*dst;

	dst = root->r_data.addr + (y * root->r_data.ll + x
			* (root->r_data.bpp / 8));
	*(unsigned int *)dst = color;
}

// Destroys the existing image and creates a new one.
// Also puts it to the window.
void	new_img(t_root *root)
{
	mlx_destroy_image(root->mlx, root->r_data.img);
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->r_data.img, 0, 0);
}

// Allows for the image to be updated in the window.
void	refresh(t_root *root)
{
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->r_data.img,
		0 + root->r_screen.x_scale, 0 + root->r_screen.y_scale);
}
