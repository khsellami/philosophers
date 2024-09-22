/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:42:01 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/17 15:57:06 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

static void	handle_single_philo(t_arg *args, t_philo *philo)
{
	print_message("has taken a fork", philo, args);
	ft_usleep(args->time_die, args);
	print_message("died", philo, args);
	pthread_mutex_lock(&args->meal_mutex);
	args->end_simulation = true;
	pthread_mutex_unlock(&args->meal_mutex);
}

static void	eat(t_philo *philo, t_arg *args)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	print_message("has taken a fork", philo, args);
	pthread_mutex_lock(&philo->right_fork->fork);
	print_message("has taken a fork", philo, args);
	print_message("is eating", philo, args);
	ft_usleep(args->time_eat, args);
	pthread_mutex_lock(&args->meal_mutex);
	philo->last_meal_time = get_time();
	philo->nbr_meal++;
	pthread_mutex_unlock(&args->meal_mutex);
	unlock_forks(philo);
}

static bool	has_reached_meal_limit(t_philo *philo, t_arg *args)
{
	bool	meal_limit_reached;

	meal_limit_reached = false;
	if (args->nbr_meat != -1)
	{
		pthread_mutex_lock(&args->meal_mutex);
		if (philo->nbr_meal >= args->nbr_meat)
			meal_limit_reached = true;
		pthread_mutex_unlock(&args->meal_mutex);
	}
	return (meal_limit_reached);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_arg	*args;

	philo = (t_philo *)arg;
	args = philo->arg;
	if (args->nbr_philo == 1)
		return (handle_single_philo(args, philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(args->time_eat, args);
	while (!check_end_simulation(args))
	{
		eat(philo, args);
		if (has_reached_meal_limit(philo, args))
			break ;
		print_message("is sleeping", philo, args);
		ft_usleep(args->time_sleep, args);
		print_message("is thinking", philo, args);
	}
	return (NULL);
}
