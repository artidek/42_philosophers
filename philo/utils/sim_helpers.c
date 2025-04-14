/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/14 23:04:04 by aobshatk         ###   ########.fr       */
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
	if (msg == 2)
		printf("%ld Philo %d has taken a fork\n", get_time(), philo);
	if (msg == 3)
		printf("%ld Philo %d is eating\n", get_time(), philo);
	if (msg == 4)
		printf("%ld Philo %d is sleeping\n", get_time(), philo);
	if (msg == 5)
		printf("%ld Philo %d has died\n", get_time(), philo);
}

void	*death_time(void *philo)
{
	t_philo *philo_n;
	long int	msec;

	philo_n = (t_philo *)philo;
	msec = 0;
	while (((int)(msec * 100) < philo_n->time_set.time_to_die))
	{
		pthread_mutex_lock(&(philo_n->alive_lock));
		if(philo_n->interupt)
		{
			pthread_mutex_unlock(&(philo_n->alive_lock));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo_n->alive_lock));
		usleep(100);
		msec++;
	}
	philo_message(5, philo_n->philo);
	philo_n->death = 1;
	return (NULL);
}

void	*sim_philos(void *philos)
{
	t_philo *philo_n;
	
	philo_n = (t_philo *)philos;
	while (1)
	{
		if (!go_eat_m(philo_n))
			return (NULL);
		if (!go_sleep(philo_n))
			return (NULL);
	}
	return (NULL);
}
