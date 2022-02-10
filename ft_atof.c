/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:28:55 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 12:49:39 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

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
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			passed_dot++;
			i++;
		}
		if (passed_dot != 0)
			passed_dot++;
		if (!(str[i] == 'i'))
		{
		nbr *= 10;
		nbr += str[i] - '0';
		}
		i++;
	}
	while (passed_dot > 1)
	{
		nbr /= 10;
		passed_dot--;
	}
	return (nbr * sign);
}
