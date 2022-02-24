/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:03:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/24 19:22:03 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>

# define WIDTH 1920
# define HEIGHT 1080 
# define FAIL 0
# define SUCCESS 1
# define MOUSE_DOWN 5
# define MOUSE_UP 4
# define ARW_UP 126
# define ARW_LEFT 123
# define ARW_DOWN 125
# define ARW_RIGHT 124
# define PAGE_UP 116
# define PAGE_DOWN 121
# define KEY_C 8
# define KEY_R 15
# define KEY_B 11
# define ESC 53
# define OFFSET 1
# define ZOOM 3
# define CHECK_I 1
# define DONT_CHECK_I 0

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endi;
}	t_data;

typedef struct s_julia {
	long double	x;
	long double	y;
}	t_julia;

typedef struct s_screen {
	int			color;
	int			all_options;
	int			options[7][3];
	int			color_type;
	int			iteri;
	long double	x_scale;
	long double	y_scale;
	long double	x_offset;
	long double	y_offset;
	long double	zoom;
	long double	escape;
}	t_screen;

typedef struct s_root {
	t_data		r_data;
	t_screen	r_screen;
	t_julia		r_julia;
	void		*mlx;
	void		*mlx_win;
	int			set;
}	t_root;

int			main(int argc, char *argv[]);
int			init_mlx(t_root *root);
void		refresh(t_root *root);
void		new_img(t_root *root);
void		my_pxl_put(t_root *root, int x, int y, int color);
void		mouse_down(t_root *root);
void		mouse_up(t_root *root);
int			mouse_hook(int button, int x, int y, t_root *root);
void		set_iteri(int key, t_root *root);
int			key_hook(int key, t_root *root);
void		check_input(int argc, char **argv, t_root *root);
void		check_input_atof(char *s, int i_check);
void		exit_error(char *error_message);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
long double	ft_atosign(char *sign);
long double	ft_atof(char *str, int i_check);
void		set_nbr_atof(int i, int *passed_dot, long double *nbr, char *str);
int			color(int r, int g, int b);
void		put_rainbow(t_root *root, int x, int y, int i);
void		put_single_color(t_root *root, int x, int y, int i);
void		put_black_to_white(t_root *root, int x, int y, int i);
void		set_color_change_type(int key, t_root *root);
void		fractal(int type, int x, int y, t_root *root);
void		color_change(t_root *root);
void		put_plot(t_root *root, int x, int y);
int			mandelbrot(t_root *root, long double x, long double y);
void		mandelbrot_helper(t_root *r, int *i,
				long double i_s, long double r_s);
int			julia(t_root *root, long double x, long double y);
int			burning_ship(t_root *root, long double x, long double y);
void		ship_helper(t_root *r, int *i,
				long double i_s, long double r_s);
#endif
