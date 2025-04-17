/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/17 21:28:26 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	(philo->message)(1, philo);
	(philo->lock)(philo);
	if(philo->death)
	{
		(philo->unlock)(philo);
		return (0);
	}
	(philo->message)(2, philo);
	(philo->message)(3, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->unlock)(philo);
	(philo->death_timer)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	(philo->message)(4, philo);
	(philo->death_timer)(philo);
	usleep(philo->time_set.time_to_sleep);
	if (philo->death)
		return (0);
	(philo->death_timer)(philo);
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	(philo->message)(1, philo);
	usleep(philo->time_set.time_to_eat);
	(philo->message)(5, philo);
	return (0);
}

void	check_death_timer(t_philo *philo)
{
	usleep(philo->time_set.time_to_die);
	philo->death = 1;
	philo_message(5, philo);
}

void	*sim_philo(void *philos)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philos;
	(philo_n->death_timer)(philo_n);
	while (1)
	{
		if (!(philo_n->eat_o)(philo_n))
			return (NULL);
		if (!(philo_n->sleep)(philo_n))
			return (NULL);
	}
	return (NULL);
}
