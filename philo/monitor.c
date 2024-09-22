/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:45:59 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/22 14:14:10 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end_simulation(t_arg *args)
{
	bool	result;

	pthread_mutex_lock(&args->meal_mutex);
	result = args->end_simulation;
	pthread_mutex_unlock(&args->meal_mutex);
	return (result);
}

static bool	check_die(t_arg *args, t_philo *philos, int i)
{
	bool	result;

	pthread_mutex_lock(&args->meal_mutex);
	result = (get_time() - philos[i].last_meal_time > args->time_die);
	pthread_mutex_unlock(&args->meal_mutex);
	return (result);
}

static bool	check_all_full(t_arg *args)
{
	int	i;

	pthread_mutex_lock(&args->meal_mutex);
	i = 0;
	while (i < args->nbr_philo)
	{
		if (args->philos[i].nbr_meal != args->nbr_meat)
		{
			pthread_mutex_unlock(&args->meal_mutex);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&args->meal_mutex);
	return (true);
}

static void	check_eat(t_arg *args)
{
	if (check_all_full(args))
	{
		pthread_mutex_lock(&args->meal_mutex);
		args->end_simulation = true;
		pthread_mutex_unlock(&args->meal_mutex);
	}
}

void	*monitor_routine(void *arg)
{
	t_arg	*args;
	t_philo	*philos;
	int		i;

	args = (t_arg *)arg;
	philos = args->philos;
	while (!check_end_simulation(args))
	{
		i = 0;
		while (i < args->nbr_philo)
		{
			if (check_end_simulation(args))
				break ;
			if (check_die(args, philos, i))
				return (handle_philosopher_death(philos, args), NULL);
			i++;
		}
		if (args->nbr_meat != -1)
			check_eat(args);
	}
	return (NULL);
}
