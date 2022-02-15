/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atosign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:30:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/02/15 13:32:52 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	ft_atosign(char *sign)
{
	int	i;

	i = 0;
	if (!sign)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	while (sign[i] != '\0')
		i++;
	if (i != 1)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	if (sign[0] == '+')
		return (1);
	else if (sign[0] == '-')
		return (-1);
	exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	return (0);
}
