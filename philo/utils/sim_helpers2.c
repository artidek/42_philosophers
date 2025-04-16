/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/16 23:22:36 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	(philo->message)(1, philo);
	(philo->lock)(philo);
	if (philo->diff(start) > philo->time_set.time_to_die)
	{
		(philo->message)(5, philo);
		philo->death = 1;
		(philo->unlock)(philo);
		return (0);
	}
	(philo->message)(2, philo);
	(philo->message)(3, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->unlock)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	(philo->message)(4, philo);
	usleep(philo->time_set.time_to_sleep);
	if (time_diff(start) > philo->time_set.time_to_die)
	{
		(philo->message)(5, philo);
		philo->death = 1;
		(philo->unlock)(philo);
		return (0);
	}
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	(philo->message)(1, philo);
	(philo->message)(2, philo);
	(philo->message)(3, philo);
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
