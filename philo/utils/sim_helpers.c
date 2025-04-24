/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/24 23:43:29 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	lock(t_philo *philo)
{
	if (&(philo->fork_lock) < &(philo->prev->fork_lock))
	{
		pthread_mutex_lock(&(philo->fork_lock));
		pthread_mutex_lock(&(philo->prev->fork_lock));
	}
	else
	{
		pthread_mutex_lock(&(philo->prev->fork_lock));
		pthread_mutex_lock(&(philo->fork_lock));
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

void	philo_message (int msg, int philo)
{
	if (msg == 1)
		printf("%ld Philo %d is thinking\n", get_time(), philo);
	else if (msg == 2)
		printf("%ld Philo %d has taken a fork\n", get_time(), philo);
	else if (msg == 3)
		printf("%ld Philo %d is eating\n", get_time(), philo);
	else if (msg == 4)
		printf("%ld Philo %d is sleeping\n", get_time(), philo);
	else if (msg == 5)
		printf("%ld Philo %d has died\n", get_time(), philo);
	usleep(100);
}

void	*sim_philos(void *philos)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philos;
	while (1)
	{
		pthread_mutex_lock(&philo_n->fork_lock);
		if (*(philo_n->sim_stop) == 1)
		{
			pthread_mutex_unlock(&philo_n->fork_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo_n->fork_lock);
		(philo_n->message)(1, philo_n->philo);
		if(!(philo_n->eat_m)(philo_n))
			return (NULL);
		if(!(philo_n->sleep)(philo_n))
			return (NULL);
	}
	return (NULL);
}
