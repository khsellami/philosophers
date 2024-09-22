/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:49:07 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/17 17:30:15 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_args(t_arg *args, char **av, int ac)
{
	args->nbr_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->nbr_meat = ft_atoi(av[5]);
	else
		args->nbr_meat = -1;
	args->start_simulation = 0;
	args->end_simulation = false;
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&args->meal_mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	init_philos(t_arg *args)
{
	int	i;

	args->philos = malloc(sizeof(t_philo) * args->nbr_philo);
	if (!args->philos)
		return (false);
	i = 0;
	while (i < args->nbr_philo)
	{
		args->philos[i].id = i + 1;
		args->philos[i].nbr_meal = 0;
		args->philos[i].last_meal_time = get_time();
		args->philos[i].full = false;
		args->philos[i].left_fork = &args->forks[i];
		args->philos[i].right_fork = &args->forks[(i + 1) % args->nbr_philo];
		args->philos[i].arg = args;
		i++;
	}
	return (true);
}

bool	init_forks(t_arg *args)
{
	int	i;

	args->forks = malloc(sizeof(t_fork) * args->nbr_philo);
	if (!args->forks)
		return (false);
	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_mutex_init(&args->forks[i].fork, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	handle_philosopher_death(t_philo *philo, t_arg *args)
{
	print_message("died", philo, args);
	pthread_mutex_lock(&args->meal_mutex);
	args->end_simulation = true;
	pthread_mutex_unlock(&args->meal_mutex);
}

bool	create_threads(t_arg *args)
{
	int	i;

	i = 0;
	args->start_simulation = get_time();
	while (i < args->nbr_philo)
	{
		if (pthread_create(&args->philos[i].thread_philo, \
		NULL, &philo_routine, &args->philos[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&args->monitor_thread, NULL, \
	&monitor_routine, args) != 0)
		return (false);
	return (true);
}
