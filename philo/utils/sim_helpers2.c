/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/14 23:16:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	long int	start;
	long int	diff;

	start = 1000000 - get_time();
	printf("start %ld\n", start);
	philo_message(1, philo->philo);
	(philo->lock)(philo);
	diff = start + get_time();
	printf("diff %ld\n", diff);
	if (diff > philo->time_set.time_to_die)
	{
		philo_message(5, philo->philo);
		philo->death = 1;
		(philo->unlock)(philo);
		return (0);
	}
	philo_message(2, philo->philo);
	philo_message(3, philo->philo);
	usleep(philo->time_set.time_to_eat);
	(philo->unlock)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	long int	start;
	long int	diff;

	start = 1000000 - get_time();
	philo_message(4, philo->philo);
	usleep(philo->time_set.time_to_sleep);
	diff = start + get_time();
	if (diff > philo->time_set.time_to_die)
	{
		philo->death = 1;
		philo_message(5, philo->philo);
		return (0);
	}
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	philo_message(1, philo->philo);
	philo_message(2, philo->philo);
	philo_message(3, philo->philo);
	usleep(philo->time_set.time_to_eat);
	return (1);
}

void	*sim_philo(void *philos)
{
	t_philo *philo_n;
	
	philo_n = (t_philo *)philos;
	while (1)
	{
		if (!go_eat_o(philo_n))
			return (NULL);
		if (!go_sleep(philo_n))
			return (NULL);
	}
	return (NULL);
}
