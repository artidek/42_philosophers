/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/18 12:17:20 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	(philo->lock)(philo);
	philo->stop_timer = 1;
	(philo->message)(3, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->unlock)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	(philo->message)(4, philo);
	usleep(philo->time_set.time_to_sleep);
	philo->stop_timer = 1;
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	(philo->message)(1, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->message)(5, philo);
	return (0);
}

void	*check_death_timer(void *philo)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philo;
	while (1)
	{
		usleep(philo_n->time_set.time_to_die);
		if (!philo_n->stop_timer)
		{
			philo_n->message(5, philo_n);
			philo_n->death = 1;
			return (NULL);
		}
		philo_n->stop_timer = 0;
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
