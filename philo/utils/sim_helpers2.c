/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/23 20:59:10 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	(philo->lock)(philo);
	usleep(1000);
	philo->stop_timer = 1;
	(philo->message)(2, philo);
	(philo->message)(2, philo);
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
	int dt;
	int tm;

	philo_n = (t_philo *)philo;
	dt = philo_n->time_set.time_to_die;
	tm = 0;
	while (1)
	{
		usleep(1000);
		tm += 1000;
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
