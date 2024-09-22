/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:49:03 by ksellami          #+#    #+#             */
/*   Updated: 2024/09/17 17:28:47 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				nbr_meal;
	long			last_meal_time;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_philo;
	struct s_arg	*arg;
}	t_philo;

typedef struct s_arg
{
	int				nbr_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nbr_meat;
	long			start_simulation;
	bool			end_simulation;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
}	t_arg;

int		valid_input(int ac, char **av);
void	*philo_routine(void *arg);
bool	check_end_simulation(t_arg *args);
void	*monitor_routine(void *arg);
bool	init_args(t_arg *args, char **av, int ac);
bool	init_philos(t_arg *args);
bool	init_forks(t_arg *args);
bool	create_threads(t_arg *args);
long	get_time(void);
void	ft_usleep(long time, t_arg *args);
void	print_message(char *s, t_philo *philo, t_arg *args);
void	free_all(t_arg *args);
int		ft_atoi(char *s);
int		ft_is_digit(char c);
int		ft_is_space(char c);
void	handle_philosopher_death(t_philo *philo, t_arg *args);

#endif
