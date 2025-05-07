/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:39:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/07 21:23:55 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	set_time(char **argv, t_time_set *time_set)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	time_set->start_time = tm.tv_sec;
	time_set->time_to_die = (long int)ft_atoil(argv[2]);
	time_set->time_to_eat = (long int)ft_atoil(argv[3]);
	time_set->time_to_sleep = (long int)ft_atoil(argv[4]);
	if (!argv[5])
		time_set->num_of_eats = -1;
	else
		time_set->num_of_eats = (int)ft_atoil(argv[5]);
}

static t_philo	*last_philo(t_philo *philos)
{
	if (!philos)
		return (NULL);
	if (!philos->next)
		return (philos);
	while (philos->next)
		philos = philos->next;
	return (philos);
}

static t_philo	*new_philo(t_time_set time_set, int philo, t_semaphors semaphors)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->philo_set.time_set = time_set;
	new_philo->philo_set.semaphors = semaphors;
	new_philo->philo_set.philo = philo;
	new_philo->philo_set.num_eaten = 0;
	new_philo->philo_set.last_eat = 0;
	new_philo->next = NULL;
	return (new_philo);
}

static void	add_philo(t_philo **philos, t_philo *new_philo)
{
	t_philo	*lst_philo;

	if (!philos)
		return ;
	if (!new_philo && *philos)
	{
		free(philos);
		return ;
	}
	if (!*philos)
	{
		*philos = new_philo;
		return ;
	}
	lst_philo = last_philo(*philos);
	lst_philo->next = new_philo;
}

void	init_philos(t_time_set *time_set, t_philo **philos, char **argv, t_semaphors *semaphors)
{
	int	num_philos;
	int	i;

	num_philos = (int)ft_atoil(argv[1]);
	i = 0;
	set_time(argv, time_set);
	init_semaphors(semaphors, num_philos);
	while (i < num_philos)
	{
		i++;
		add_philo(philos, new_philo(*time_set, i, *semaphors));
	}
}
