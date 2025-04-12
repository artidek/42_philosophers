/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/12 23:09:14 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	lock(t_philo *philo, int select)
{
	if (select == 1)
	{
		if (philo->prev)
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
		else
			pthread_mutex_lock(&(philo->fork_lock));
	}
	if (select == 2)
		pthread_mutex_lock(&(philo->death_timer.death_timer_lock));
}

void	unlock(t_philo *philo, int select)
{
	if (select == 1)
	{
		if (philo->prev)
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
		else
			pthread_mutex_unlock(&(philo->fork_lock));
	}
	if (select == 2)
		pthread_mutex_unlock(&(philo->death_timer.death_timer_lock));
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

int	check_death (t_philo *philo)
{
	lock(philo, 2);
	if (philo->death)
		{
			philo_message(5, philo->philo);
			unlock(philo, 2);
			unlock(philo, 1);
			return (1);
		}
	unlock(philo, 2);
	return (0);
}
