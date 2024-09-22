/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:49:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/17 17:31:06 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lance_program(t_arg *args, char **av, int ac)
{
	int	i;

	if (!args)
		return (0);
	if (!init_args(args, av, ac) || !init_forks(args))
		return (0);
	if (!init_philos(args))
		return (free(args->forks), 0);
	if (!create_threads(args))
		return (free_all(args), 0);
	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_join(args->philos[i].thread_philo, NULL) != 0)
			return (free_all(args), 0);
		i++;
	}
	if (pthread_join(args->monitor_thread, NULL) != 0)
		return (free_all(args), 0);
	return (free_all(args), 1);
}

int	main(int ac, char **av)
{
	t_arg	args;

	if (!valid_input(ac, av))
		return (write(2, "Invalid input", 14), 1);
	if (!lance_program(&args, av, ac))
		return (1);
	return (0);
}
