/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/28 18:27:33 by aobshatk         ###   ########.fr       */
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
	pthread_mutex_unlock(philo->message_lock);
}

static int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->alive_lock);
	if (*(philo->sim_stop) == 1)
	{
		pthread_mutex_unlock(philo->alive_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->alive_lock);
	return (0);
}

int	go_eat_m(t_philo *philo)
{
	if (check_stop(philo))
		return (0);
	lock(philo);
	if (check_stop(philo))
	{
		unlock(philo);
		return (0);
	}
	message(philo, 1, get_time());
	usleep(500);
	message(philo, 1, get_time());
	usleep(500);
	if (check_stop(philo))
		return (0);
	message(philo, 2, get_time());
	usleep(philo->time_set.time_to_eat);
	unlock(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	if (check_stop(philo))
		return (0);
	message(philo, 3, get_time());
	usleep(philo->time_set.time_to_sleep);
	return (1);
}

void	*sim_philos(void *philos)
{
	t_philo	*philo_n;

	philo_n = (t_philo *)philos;
	pthread_mutex_lock(philo_n->eat_lock);
	(*philo_n->last_eat) = get_stop_time();
	pthread_mutex_unlock(philo_n->eat_lock);
	while (1)
	{
		if (check_stop(philo_n))
			return (0);
		message(philo_n, 0, get_time());
		if (!go_eat_m(philo_n))
			return (NULL);
		pthread_mutex_lock(philo_n->eat_lock);
		(*philo_n->last_eat) = get_stop_time();
		pthread_mutex_unlock(philo_n->eat_lock);
		if (check_stop(philo_n))
			return (NULL);
		philo_n->num_eaten += 1;
		if (!go_sleep(philo_n))
			return (NULL);
		if (philo_n->time_set.num_of_eats == philo_n->num_eaten)
			return (NULL);
	}
}
