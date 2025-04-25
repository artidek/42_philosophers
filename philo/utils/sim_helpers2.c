/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/25 16:14:41 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	first_fork = &(philo->fork_lock);
	second_fork = &(philo->prev->fork_lock);
	if (first_fork < second_fork)
	{
		pthread_mutex_lock(first_fork);
		pthread_mutex_lock(second_fork);
	}
	else
	{
		pthread_mutex_lock(second_fork);
		pthread_mutex_lock(first_fork);
	}
}

void	unlock(t_philo *philo)
{
	if (&(philo->fork_lock) < &(philo->prev->fork_lock))
	{
		pthread_mutex_unlock(&(philo->fork_lock));
		pthread_mutex_unlock(&(philo->prev->fork_lock));
	}
	else
	{
		pthread_mutex_unlock(&(philo->prev->fork_lock));
		pthread_mutex_unlock(&(philo->fork_lock));
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
