/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atosign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:30:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/10 13:44:23 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	ft_atosign(char *sign)
{
	int	i;

	i = 0;
	if (!sign)
		exit_with_error(1);
	while (sign[i] != '\0')
		i++;
	if (i != 1)
		exit_with_error(1);
	if (sign[0] == '+')
		return (1);
	else if (sign[0] == '-')
		return (-1);
	exit_with_error(1);
	return (0);
}
