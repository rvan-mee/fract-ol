#ifndef TESTING_H
# define TESTING_H
# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endi;
}	data;

typedef struct s_screen {
	int		color;
	int		iteri;
	double	x_scale;
	double	y_scale;
	double	x_offset;
	double 	y_offset;
	double	zoom;
	double	escape;
}	screen;

typedef struct s_root {
	data	r_data;
	screen	r_screen;
	void	*mlx;
	void	*mlx_win;
	int		set;
}	r_root;

void 	refresh(r_root *root);
void	my_pxl_put(r_root *root, int x, int y, int color);
void 	color_change(r_root *root);
int		key_hook(int keycode, r_root *root);
int		init_mlx(r_root *root);


#endif
