/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/18 12:27:26 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	mutex_cleanup(t_philo *philos)
{
	while(philos)
	{
		pthread_mutex_destroy(&(philos->alive_lock));
		pthread_mutex_destroy(&(philos->fork_lock));
		philos = philos->next;
	}
}

void	lock(t_philo *philo)
{
	if (&(philo->fork_lock) < &(philo->prev->fork_lock))
	{
		pthread_mutex_lock(&(philo->fork_lock));
		(philo->message)(2, philo);
		usleep(1000);
		pthread_mutex_lock(&(philo->prev->fork_lock));
		(philo->message)(2, philo);
		usleep(1000);
	}
	else
	{
		pthread_mutex_lock(&(philo->prev->fork_lock));
		(philo->message)(2, philo);
		usleep(1000);
		pthread_mutex_lock(&(philo->fork_lock));
		(philo->message)(2, philo);
		usleep(1000);
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

void	philo_message (int msg, t_philo *philo)
{
	if (msg == 1)
		printf("%ld Philo %d is thinking\n", get_time(), philo->philo);
	else if (msg == 2)
		printf("%ld Philo %d has taken a fork\n", get_time(), philo->philo);
	else if (msg == 3)
		printf("%ld Philo %d is eating\n", get_time(), philo->philo);
	else if (msg == 4)
		printf("%ld Philo %d is sleeping\n", get_time(), philo->philo);
	else if (msg == 5)
		printf("%ld Philo %d has died\n", get_time(), philo->philo);
	usleep(100);
}

void	*sim_philos(void *philos)
{
	t_philo *philo_n;
	pthread_t	deatht_timer;

	philo_n = (t_philo *)philos;
	pthread_create(&deatht_timer, NULL, check_death_timer, philos);
	pthread_detach(deatht_timer);
	while (1)
	{
		(philo_n->message)(1, philo_n);
		usleep(1000);
		(philo_n->eat_m)(philo_n);
		usleep(500);
		(philo_n->sleep)(philo_n);
		usleep(500);
		if (philo_n->death)
			return (NULL);
	}
	return (NULL);
}
