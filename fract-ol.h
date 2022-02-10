/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fract-ol.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:03:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 12:52:07 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
# define TESTING_H
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
# define ARROW_UP 126
# define ARROW_LEFT 123
# define ARROW_DOWN 125
# define ARROW_RIGHT 124
# define PAGE_UP 116
# define PAGE_DOWN 121
# define KEY_C 8
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
}	r_root;

int			main(int argc, char *argv[]);
int			init_mlx(r_root *root);
void		refresh(r_root *root);
void		new_img(r_root *root);
void		my_pxl_put(r_root *root, int x, int y, int color);
void		mouse_down(r_root *root);
void		mouse_up(r_root *root);
int			mouse_hook(int button, int x, int y, r_root *root);
int			key_hook(int key, r_root *root);
void		check_input(int argc, char **argv, r_root *root);
void		check_input_atof(char *s, int i_check);
void 		exit_with_error(int error_message);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
long double	ft_atosign(char *sign);
long double	ft_atof(char *str, int i_check);
int			color(int r, int g, int b);
void		put_color(r_root *root, int x, int y, int i);
void		color_change(r_root *root);
void		put_plot(r_root *root, int x, int y);
int			mandelbrot(r_root *root, long double x, long double y);
int			julia(r_root *root, long double x, long double y);
#endif
