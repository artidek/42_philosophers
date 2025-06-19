/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 16:11:21 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	message(t_philo *philo, int msg, long int timestamp)
{
	pthread_mutex_lock(philo->message_lock);
	if (msg == 0)
		printf("%ld %d is thinking\n", timestamp, philo->philo);
	if (msg == 1)
		printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	if (msg == 2)
		printf("%ld %d is eating\n", timestamp, philo->philo);
	if (msg == 3)
		printf("%ld %d is sleeping\n", timestamp, philo->philo);
	if (msg == 4)
		printf("%ld %d died\n", timestamp, philo->philo);
	if (msg == 5)
		printf("%ld everybody has eaten enough\n", timestamp);
	pthread_mutex_unlock(philo->message_lock);
}

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

void	philo_delay(t_philo *philo, long int delay)
{
	long int	start;

	start = get_time(philo->time_set.start_time);
	while (get_time(philo->time_set.start_time) - start < delay)
		usleep(20);
}

int	everybody_eaten(t_philo *philo)
{
	long int	l_eat;

	while (philo)
	{
		pthread_mutex_lock(philo->eat_lock);
		l_eat = (*philo->last_eat);
		pthread_mutex_unlock(philo->eat_lock);
		if (l_eat > -1)
			return (0);
		philo = philo->next;
	}
	return (1);
}
