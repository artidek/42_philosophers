/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/17 16:19:22 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	(philo->message)(1, philo);
	(philo->death_timer)(philo, philo->start);
	(philo->lock)(philo);
	if (!philo->death)
		philo->stop_timer = 1;
	else
	{
		(philo->unlock)(philo);
		return (0);
	}
	if (philo->stop_timer)
		philo->stop_timer = 0;
	(philo->message)(2, philo);
	(philo->message)(3, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->unlock)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	gettimeofday(&philo->start, NULL);
	(philo->message)(4, philo);
	(philo->death_timer)(philo, philo->start);
	usleep(philo->time_set.time_to_sleep);
	if (!philo->death)
		philo->stop_timer = 1;
	else
		return (0);
	if (philo->stop_timer)
		philo->stop_timer = 0;
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	(philo->message)(1, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->message)(5, philo);
	return (0);
}

void	check_death_timer(t_philo *philo, struct timeval start)
{
	while (!philo->stop_timer)
	{
		usleep(500);
		if (time_diff(start) > philo->time_set.time_to_die)
		{
			(philo->message)(5, philo);
			philo->death = 1;
			(philo->unlock)(philo);
			return;
		}
	}
}

void	*sim_philo(void *philos)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philos;
	while (1)
	{
		if (!(philo_n->eat_o)(philo_n))
			return (NULL);
		if (!(philo_n->sleep)(philo_n))
			return (NULL);
	}
	return (NULL);
}
