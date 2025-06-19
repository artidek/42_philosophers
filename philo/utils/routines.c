/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 16:25:34 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	eat(t_philo *philo)
{
	if (check_stop(philo))
		return (0);
	lock(philo);
	if (check_stop(philo))
	{
		unlock(philo);
		return (0);
	}
	message(philo, 1, get_time(philo->time_set.start_time));
	usleep(500);
	message(philo, 1, get_time(philo->time_set.start_time));
	usleep(500);
	if (check_stop(philo))
		return (0);
	message(philo, 2, get_time(philo->time_set.start_time));
	pthread_mutex_lock(philo->eat_lock);
	(*philo->last_eat) = get_time(philo->time_set.start_time);
	pthread_mutex_unlock(philo->eat_lock);
	philo_delay(philo, philo->time_set.time_to_eat);
	unlock(philo);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	if (check_stop(philo))
		return (0);
	message(philo, 3, get_time(philo->time_set.start_time));
	philo_delay(philo, philo->time_set.time_to_sleep);
	return (1);
}

void	*sim_philos(void *philos)
{
	t_philo	*philo_n;

	philo_n = (t_philo *)philos;
	while (1)
	{
		if (check_stop(philo_n))
			return (0);
		message(philo_n, 0, get_time(philo_n->time_set.start_time));
		philo_delay(philo_n, 1);
		if (!eat(philo_n))
			return (NULL);
		if (check_stop(philo_n))
			return (NULL);
		philo_n->num_eaten += 1;
		if (philo_n->time_set.num_of_eats == philo_n->num_eaten)
		{
			pthread_mutex_lock(philo_n->eat_lock);
			(*philo_n->last_eat) = -1;
			pthread_mutex_unlock(philo_n->eat_lock);
			return (NULL);
		}
		if (!p_sleep(philo_n))
			return (NULL);
	}
}

void	*sim_philo(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	init_mutexes(philo);
	printf("%ld %d is thinking\n", get_time(philo->time_set.start_time),
		philo->philo);
	printf("%ld %d has taken a fork\n", get_time(philo->time_set.start_time),
		philo->philo);
	philo_delay(philo, philo->time_set.time_to_die);
	printf("%ld %d died\n", get_time(philo->time_set.start_time), philo->philo);
	return (NULL);
}
