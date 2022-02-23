/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:23:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/23 13:20:10 by rvan-mee      ########   odam.nl         */
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
void	exit_error(char *error_message)
{
	write (1, error_message, ft_strlen(error_message));
	exit(1);
}

// Checks if the input for atof is correct.
// Returns an error with exit_error if it fails the checks.
// Can check for imaginary numbers if specified.
void	check_input_atof(char *s, int i_check)
{
	int		i;
	int		passed_dot;
	int		passed_i;

	i = 0;
	passed_dot = 0;
	passed_i = 0;
	if (s[0] == '-')
		i++;
	while (s[i] != '\0' || (s[i] >= '0' && s[i] <= '9')
		|| s[i] == 'i' || s[i] == '.')
	{	
		if ((s[i] == 'i' && s[i + 1] != '\0') || (s[i] == '.' && i == 0)
			|| (s[i] == '.' && !(s[i - 1] >= '0' && s[i - 1] <= '9'))
			|| (s[i] == '.' && s[i - 1] == 'i')
			|| (s[i] == '.' && s[i + 1] == '\0')
			|| (s[i] == '.' && s[i + 1] == 'i')
			|| (s[i] == 'i' && s[i + 1] == '\0' && i == 0))
			exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
		if (s[i] == '.')
			passed_dot++;
		if (s[i] == 'i')
			passed_i++;
		i++;
	}
	if (s[i] != '\0' || passed_i != i_check || passed_dot > 1)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
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
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
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
