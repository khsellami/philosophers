/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:53:56 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/11 13:47:59 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *s)
{
	int	result;
	int	signe;
	int	i;
	int	nb;

	i = 0;
	result = 0;
	signe = 1;
	nb = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if ((*s) == '-' || (*s) == '+')
	{
		signe = 1 - 2 * (*s++ == '-');
		i++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s++ - '0');
		if (result < nb)
			return (-2);
		nb = result;
	}
	return (signe * result);
}
