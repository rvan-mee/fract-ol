/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:01:17 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/03/21 11:43:06 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Initiate all the base colors for the rainbow mode.
void	init_rainbow_colors(t_root *root)
{
	root->r_screen.rainbow_base[0] = 0x0000F0000;
	root->r_screen.rainbow_base[1] = 0x00000F000;
	root->r_screen.rainbow_base[2] = 0x0000000FF;
	root->r_screen.rainbow_base[3] = 0x000FFFF0F;
	root->r_screen.rainbow_base[4] = 0x00000FF0F;
	root->r_screen.rainbow_base[5] = 0x000FFFF00;
	root->r_screen.rainbow_base[6] = 0x000FF00FF;
	root->r_screen.rainbow_base[7] = 0x0000F00FF;
	root->r_screen.rainbow_base[8] = 0x00020F6DA;
	root->r_screen.rainbow_base[9] = 0x00000277D;
	root->r_screen.rainbow_base[10] = 0x000F00F0;
}

// Initiate all the color options.
void	init_options(t_root *root)
{
	root->r_screen.all_options = 0;
	root->r_screen.options[0][0] = 1;
	root->r_screen.options[0][1] = 0;
	root->r_screen.options[0][2] = 0;
	root->r_screen.options[1][0] = 0;
	root->r_screen.options[1][1] = 1;
	root->r_screen.options[1][2] = 0;
	root->r_screen.options[2][0] = 0;
	root->r_screen.options[2][1] = 0;
	root->r_screen.options[2][2] = 1;
	root->r_screen.options[3][0] = 1;
	root->r_screen.options[3][1] = 1;
	root->r_screen.options[3][2] = 0;
	root->r_screen.options[4][0] = 1;
	root->r_screen.options[4][1] = 0;
	root->r_screen.options[4][2] = 1;
	root->r_screen.options[5][0] = 0;
	root->r_screen.options[5][1] = 1;
	root->r_screen.options[5][2] = 1;
}

// Initiate all the MLX data and screen data.
int	init_mlx(t_root *root)
{
	init_options(root);
	init_rainbow_colors(root);
	root->mlx = mlx_init();
	if (root->mlx == NULL)
		exit_error("MLX error\n");
	root->r_screen.iteri = 100;
	root->r_screen.x_scale = 2 / (long double)HEIGHT;
	root->r_screen.y_scale = 2 / (long double)HEIGHT * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 1;
	root->r_screen.color = 0x0000FF00;
	root->r_screen.color_type = 1;
	root->mlx_win = mlx_new_window(root->mlx, WIDTH, HEIGHT, "fract-ol");
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	if (root->r_data.img == NULL || root->mlx_win == NULL)
		exit_error("MLX error\n");
	root->r_data.addr = mlx_get_data_addr(root->r_data.img,
			&root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	if (root->r_data.addr == NULL)
		exit_error("MLX error\n");
	return (0);
}

// initiates all the values to have 
// the burning ship fractol in a better position.
void	init_ship(t_root *root)
{
	root->set = 3;
	root->r_screen.zoom = 3;
	root->r_screen.x_scale = 0.00012056327160493829;
	root->r_screen.y_scale = -0.00014288980338363055;
	root->r_screen.x_offset = -1.79834876543209878344;
	root->r_screen.y_offset = 0.10413351623228167290;
}

// Calls the init functions and starts the MLX loop.
int	main(int argc, char *argv[])
{
	t_root	root;

	check_input(argc, argv, &root);
	init_mlx(&root);
	if (root.set == 3)
		init_ship(&root);
	color_change(&root);
	mlx_hook(root.mlx_win, CLOSE_WINDOW, 0, exit_error, "");
	mlx_key_hook(root.mlx_win, key_hook, &root);
	mlx_mouse_hook(root.mlx_win, mouse_hook, &root);
	mlx_loop(root.mlx);
	return (0);
}
