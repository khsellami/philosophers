/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:52:07 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/22 14:14:44 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time, t_arg *args)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time && !check_end_simulation(args))
		usleep(100);
}

void	print_message(char *s, t_philo *philo, t_arg *args)
{
	pthread_mutex_lock(&args->print_mutex);
	usleep(5);
	if (!check_end_simulation(args))
	{
		printf("%ld %d", get_time() - args->start_simulation, philo->id);
		printf(" %s\n", s);
	}
	pthread_mutex_unlock(&args->print_mutex);
}

void	free_all(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_mutex_destroy(&args->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->meal_mutex);
	free(args->forks);
	free(args->philos);
}
