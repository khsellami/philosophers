/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:23:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/22 14:14:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	positive_int(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str && ft_is_space(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		if (!positive_int(av[i]) || ft_atoi(av[i]) == -2)
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) == 0)
		return (0);
	return (1);
}
