/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:19:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/24 23:44:24 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		return (0);
	}
	pthread_mutex_unlock(&philo->alive_lock);
	(philo->message)(2, philo->philo);
	usleep(1000);
	(philo->message)(2, philo->philo);
	(philo->message)(3, philo->philo);
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
	(philo->message)(4, philo->philo);
	usleep(philo->time_set.time_to_sleep);
	return (1);
}

int	go_eat_o(t_philo *philo)
{
	(philo->message)(1, philo->philo);
	usleep(philo->time_set.time_to_eat);
	(philo->message)(5, philo->philo);
	return (0);
}

void	check_death_timer(void *philo)
{
	t_philo	*temp;

	while (1)
	{
		temp = philo;
		while (temp)
		{
			pthread_mutex_lock(&temp->alive_lock);
			if (get_stop_time() - temp->last_eat >= temp->time_set.time_to_die / 1000)
			{
				(temp->message)(5, temp->philo);
				*(temp->sim_stop) = 1;
				pthread_mutex_unlock(&temp->alive_lock);
				return;
			}
			pthread_mutex_unlock(&temp->alive_lock);
			temp = temp->next;
		}
	}
}

void	*sim_philo(void *philos)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philos;
	while (1)
	{
		if (!(philo_n->eat_o)(philo_n))
			return (NULL);
		if (!(philo_n->sleep)(philo_n))
			return (NULL);
	}
	return (NULL);
}
