/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:23:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 15:14:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_with_error(int error_message)
{
	if (error_message == 1)
		write(1, "Please use a valid constant\nTry this: 0.285 + 0.01i\n", 53);
	if (error_message == 2)
		write(1, "Please use a valid argument\nmandelbrot\njulia\nvela\n", 50);
	exit(1);
}

void	check_input_atof(char *s, int i_check)
{
	int		i;
	int		passed_dot;
	int		passed_i;

	i = 0;
	passed_dot = 0;
	passed_i = 0;
	if (s[i] == '-')
		i++;
	while (s[i] != '\0' || (s[i] >= '0' && s[i] <= '9') || s[i] == 'i' || s[i] == '.')
	{	
		if ((s[i] == 'i' && s[i + 1] != '\0') || (s[i] == '.' && i == 0)
			|| (s[i] == '.' && !(s[i - 1] >= '0' && s[i - 1] <= '9'))
			|| (s[i] == '.' && s[i - 1] == 'i') || (s[i] == '.' && s[i + 1] == '\0')
			|| (s[i] == '.' && s[i + 1] == 'i') || (s[i] == 'i' && s[i + 1] == '\0' && i == 0))
			exit_with_error(1);
		if (s[i] == '.')
			passed_dot++;
		if (s[i] == 'i')
			passed_i++;
		i++;
	}
	if (s[i] != '\0' || passed_i != i_check || passed_dot > 1)
		exit_with_error(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n)
	{
		if ((str1[i] == '\0') || (str2[i] == '\0') || (str1[i] != str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	check_input(int argc, char **argv, t_root *root)
{
	if (argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 11)))
		root->set = 1;
	else if (argc == 2 && !(ft_strncmp(argv[1], "vela", 5)))
		root->set = 3;
	else if (argc == 2 && !(ft_strncmp(argv[1], "julia", 6)))
		exit_with_error(1);
	else if (argc == 3 && !(ft_strncmp(argv[1], "julia", 6)))
	{
		root->set = 2;
		root->r_julia.x = 0;
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I);
	}
	else if (argc == 5 && !(ft_strncmp(argv[1], "julia", 6)))
	{
		root->set = 2;
		root->r_julia.x = ft_atof(argv[argc - 3], DONT_CHECK_I);
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I)
			* ft_atosign(argv[argc - 2]);
	}
	else
		exit_with_error(2);
}

