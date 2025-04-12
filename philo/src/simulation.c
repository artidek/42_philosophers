/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/12 23:10:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static void	*death_time(void *philo)
{
	t_philo *philo_n;

	philo_n = (t_philo *)philo; 
	while (1)
	{
		usleep (philo_n->time_set.time_to_die);
		while (philo_n)
		{
			if (philo_n->death == 1)
				return (NULL);
			else
			{
				lock(philo_n, 2);
				philo_n->death = 1;
				unlock(philo_n, 2);
			}
			philo_n = philo_n->next;
		}
		philo_n = (t_philo *)philo;
	}
	return (NULL);
}

static void	*sim_philo(void *philos)
{
	t_philo *philo_n;
	
	philo_n = (t_philo *)philos;
	while(1)
	{
		philo_message(1, philo_n->philo);
		lock(philo_n, 1);
		if (check_death(philo_n))
			return (NULL);
		philo_message(2, philo_n->philo);
		philo_message(3, philo_n->philo);
		usleep(philo_n->time_set.time_to_eat);
		unlock(philo_n, 1);
		lock(philo_n, 2);
		philo_n->death = 0;
		unlock(philo_n, 2);
		philo_message(4, philo_n->philo);
		usleep(philo_n->time_set.time_to_sleep);
	}
	return (NULL);
}

void	start_sim (t_philo *philos)
{
	t_philo *temp = philos;
	t_lock d_lock;

	pthread_mutex_init(&(d_lock.death_timer_lock), NULL);
	pthread_create(&(d_lock.death_timer), NULL, &death_time, temp);
	while(temp)
	{
		temp->death_timer = d_lock;
		pthread_mutex_init(&(temp->fork_lock), NULL);
		pthread_create(&(temp->thrd_philo), NULL, &sim_philo, temp);
		temp = temp->next;
	}
	temp = philos;
	while (temp)
	{
		pthread_join(temp->thrd_philo, NULL);
		temp = temp->next;
	}
	pthread_join(d_lock.death_timer, NULL);
}
