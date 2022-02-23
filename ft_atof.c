/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:28:55 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/23 13:50:58 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Helper fuction of atof, sets all the converted chars in front of the decimal
// point and counts how many numbers should be past it.
void	set_nbr_atof(int i, int *passed_dot, long double *nbr, char *str)
{
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			(*passed_dot)++;
			i++;
		}
		if (*passed_dot != 0)
			(*passed_dot)++;
		if (!(str[i] == 'i'))
		{
			*nbr *= 10;
			*nbr += str[i] - '0';
		}
		i++;
	}
}

// Takes a string and converts it into a long double.
long double	ft_atof(char *str, int i_check)
{
	int			i;
	int			passed_dot;
	long double	sign;
	long double	nbr;

	check_input_atof(str, i_check);
	i = 0;
	nbr = 0;
	sign = 1;
	passed_dot = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	set_nbr_atof(i, &passed_dot, &nbr, str);
	while (passed_dot > 1)
	{
		nbr /= 10;
		passed_dot--;
	}
	return (nbr * sign);
}
