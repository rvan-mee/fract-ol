/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:01:17 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/23 13:28:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Initiate all the color values.
void	init_colors(t_root *root)
{
	root->r_screen.all_options[0] = 0x000FF0000;
	root->r_screen.all_options[1] = 0x00000F000;
	root->r_screen.all_options[2] = 0x0000000FF;
	root->r_screen.all_options[3] = 0x000FF00FF;
	root->r_screen.all_options[4] = 0x00000FF0F; // change
	root->r_screen.all_options[5] = 0x000FFFF00;
	root->r_screen.all_options[6] = 0x000FFFF0F; // change
	root->r_screen.all_options[7] = 0x000FF7DFF;
	root->r_screen.all_options[8] = 0x00020F6DA;
	root->r_screen.all_options[9] = 0x000FF277D;
	root->r_screen.all_options[10] = 0x000FF6F1F;
}

// Initiate all the MLX data and screen data.
int	init_mlx(t_root *root)
{
	init_colors(root);
	root->mlx = mlx_init();
	root->r_screen.iteri = 100;
	root->r_screen.x_scale = 3 / (long double)WIDTH;
	root->r_screen.y_scale = 2 / (long double)HEIGHT * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 1;
	root->r_screen.color = 0x000000FF;
	root->r_screen.color_type = 1;
	root->mlx_win = mlx_new_window(root->mlx, WIDTH, HEIGHT, "fract-ol");
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	root->r_data.addr = mlx_get_data_addr(root->r_data.img,
			&root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	color_change(root);
	return (0);
}

// Calls the init functions and starts the MLX loop.
int	main(int argc, char *argv[])
{
	t_root	root;

	check_input(argc, argv, &root);
	init_mlx(&root);
	mlx_key_hook(root.mlx_win, key_hook, &root);
	mlx_mouse_hook(root.mlx_win, mouse_hook, &root);
	mlx_loop(root.mlx);
	return (0);
}
