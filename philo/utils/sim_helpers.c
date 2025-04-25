/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/25 17:12:27 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	go_eat_m(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive_lock);
	if (*(philo->sim_stop) == 1)
	{
		pthread_mutex_unlock(&philo->alive_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->alive_lock);
	(philo->lock)(philo);
	pthread_mutex_lock(&philo->alive_lock);
	if (*(philo->sim_stop) == 1)
	{
		pthread_mutex_unlock(&philo->alive_lock);
		(philo->unlock)(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->alive_lock);
	printf("%ld %d has taken a fork\n", get_time(), philo->philo);
	printf("%ld %d has taken a fork\n", get_time(), philo->philo);
	usleep(1000);
	printf("%ld %d is eating\n", get_time(), philo->philo);
	philo->last_eat = get_stop_time();
	usleep(philo->time_set.time_to_eat);
	philo->last_eat = get_stop_time();
	(philo->unlock)(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive_lock);
	if (*(philo->sim_stop) == 1)
	{
		pthread_mutex_unlock(&philo->alive_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->alive_lock);
	printf("%ld %d is sleeping\n", get_time(), philo->philo);
	usleep(philo->time_set.time_to_sleep);
	return (1);
}

void	*sim_philos(void *philos)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philos;
	usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo_n->alive_lock);
		if (*(philo_n->sim_stop) == 1)
		{
			pthread_mutex_unlock(&philo_n->alive_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo_n->alive_lock);
		printf("%ld %d is thinking\n", get_time(), philo_n->philo);
		usleep(500);
		if(!(philo_n->eat_m)(philo_n))
			return (NULL);
		philo_n->num_eaten += 1;
		if(!(philo_n->sleep)(philo_n))
			return (NULL);
		if (philo_n->time_set.num_of_eats == philo_n->num_eaten)
		{
			return (NULL);
		}
	}
}
