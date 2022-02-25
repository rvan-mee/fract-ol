/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:01:17 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/25 13:31:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	root->r_screen.options[6][0] = 1;
	root->r_screen.options[6][1] = 0;
	root->r_screen.options[6][2] = 1;
}

// Initiate all the MLX data and screen data.
int	init_mlx(t_root *root)
{
	init_options(root);
	root->mlx = mlx_init();
	if (root->mlx == NULL)
		exit_error("MLX error\n");
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
	if (root->r_data.img == NULL || root->mlx_win == NULL)
		exit_error("MLX error\n");
	root->r_data.addr = mlx_get_data_addr(root->r_data.img,
			&root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	if (root->r_data.addr == NULL)
		exit_error("MLX error\n");
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
