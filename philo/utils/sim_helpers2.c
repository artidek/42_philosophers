/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/28 17:33:43 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->fork_lock;
	second = philo->prev->fork_lock;
	if (first < second)
	{
		pthread_mutex_lock(first);
		pthread_mutex_lock(second);
	}
	else
	{
		pthread_mutex_lock(second);
		pthread_mutex_lock(first);
	}
}

void	unlock(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->fork_lock;
	second = philo->prev->fork_lock;
	if (first < second)
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
	}
	else
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
	}
}

void	*sim_philo(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	printf("%ld %d is thinking\n", get_time(), philo->philo);
	usleep(philo->time_set.time_to_die);
	printf("%ld %d died\n", get_time(), philo->philo);
	return (NULL);
}
