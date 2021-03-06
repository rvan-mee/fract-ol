/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:23:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/03/21 11:41:09 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Returns the length of a string.
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// Exits program with a selected error message written beforehand.
int	exit_error(char *error_message)
{
	write (1, error_message, ft_strlen(error_message));
	exit(1);
	return (1);
}

// Compares 2 strings with one another.
// Returns the difference in ascii if there is one.
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

// Checks if the command line input is correct and selects the proper settings.
void	check_input(int argc, char **argv, t_root *root)
{
	if (argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 11)))
		root->set = 1;
	else if (argc == 2 && !(ft_strncmp(argv[1], "vela", 5)))
		root->set = 3;
	else if (argc == 2 && !(ft_strncmp(argv[1], "julia", 6)))
		exit_error("Use a valid constant\nTry 0.285 + 0.01i\nOr try 0.8i\n");
	else if (argc == 3 && !(ft_strncmp(argv[1], "julia", 6)))
	{
		root->set = 2;
		root->r_screen.iteri = 10;
		root->r_julia.x = 0;
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I);
	}
	else if (argc == 5 && !(ft_strncmp(argv[1], "julia", 6)))
	{
		root->set = 2;
		root->r_screen.iteri = 10;
		root->r_julia.x = ft_atof(argv[argc - 3], DONT_CHECK_I);
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I)
			* ft_atosign(argv[argc - 2]);
	}
	else
		exit_error("Please use a valid argument\nmandelbrot\njulia\nvela\n");
}
