/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 23:39:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	message(t_philo *philo, int msg, int death)
{
	pthread_mutex_lock(philo->message_lock);
	if (msg == 1 && !death)
		printf("%ld %d has taken a fork\n", get_time(philo), philo->philo);
	else if (msg == 2 && !death)
		printf("%ld %d is eating\n", get_time(philo), philo->philo);
	else if ((msg == 1 || msg == 2) && death)
	{
		pthread_mutex_unlock(philo->message_lock);
		unlock(philo);
		return (0);
	}
	if (msg == 0 && !death)
		printf("%ld %d is thinking\n", get_time(philo), philo->philo);
	else if (msg == 3 && !death)
		printf("%ld %d is sleeping\n", get_time(philo), philo->philo);
	else if (msg == 4)
		printf("%ld %d died\n", get_time(philo), philo->philo);
	else if ((msg == 0 || msg == 3) && death)
	{
		pthread_mutex_unlock(philo->message_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->message_lock);
	return (1);
}

int	check_stop(t_philo *philo, long int now)
{
	if (*(philo->sim_stop) == 1)
		return (1);
	if (absl(*(philo->last_eat) - now) > philo->time_set.time_to_die + 9)
	{
		message(philo, DIED, 1);
		*(philo->sim_stop) = 1;
		return (1);
	}
	return (0);
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

void	philo_delay (t_philo *philo, long int stop)
{
	long int	start;
	long int	now;

	start = get_time(philo);
	now = get_time(philo);
	while (now - start < stop)
	{
		usleep(50);
		now = get_time(philo);
		if (check_stop(philo, now))
			return;
	}	
}

/*void	start_delay(t_philo *philo, long int delay)
{
	long int	stop;
	long int	now;

	stop = philo->time_set.start_delay + delay;
	now = get_time(philo);
	while (now < stop)
	{
		usleep(50);
		now = get_time(philo);
	}
}*/
