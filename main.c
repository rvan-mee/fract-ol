/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:01:17 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 13:49:13 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init_mlx(t_root *root)
{
	root->mlx = mlx_init();
	root->r_screen.iteri = 100;
	root->r_screen.x_scale = 3 / (long double)WIDTH;
	root->r_screen.y_scale = 2 / (long double)HEIGHT * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 1;
	root->r_screen.color = 0x0000000F;
	root->mlx_win = mlx_new_window(root->mlx, WIDTH, HEIGHT, "testing!");
	root->r_data.img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	root->r_data.addr = mlx_get_data_addr(root->r_data.img,
			&root->r_data.bpp, &root->r_data.ll, &root->r_data.endi);
	color_change(root);
	return (0);
}

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
