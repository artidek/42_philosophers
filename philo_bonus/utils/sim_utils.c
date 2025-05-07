/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/07 21:04:16 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	message(int philo, long int start_time, int msg)
{
	if (msg == 1)
		printf("%ld %d has taken a fork\n", get_time(start_time), philo);
	if (msg == 2)
		printf("%ld %d is eating\n", get_time(start_time), philo);
	if (msg == 0)
		printf("%ld %d is thinking\n", get_time(start_time), philo);
	if (msg == 3)
		printf("%ld %d is sleeping\n", get_time(start_time), philo);
	if (msg == 4)
		printf("%ld %d died\n", get_time(start_time), philo);
	return (1);
}

void	*check_death(void *philo)
{
	t_philo	*temp;
	long int	now;

	temp = (t_philo *)philo;
	while (1)
	{
		now = get_time(temp->philo_set.time_set.start_time);
		sem_wait(temp->philo_set.semaphors.sem_alive);
		if (now - temp->philo_set.last_eat >= temp->philo_set.time_set.time_to_die + 8)
		{
			sem_post(temp->philo_set.semaphors.sem_alive);
			exit(DIED);
		}
		sem_post(temp->philo_set.semaphors.sem_alive);
		usleep(1);
	}
}

void	philo_delay(t_time_set time_set, long int stop)
{
	long int	start;
	long int	now;

	start = get_time(time_set.start_time);
	now = get_time(time_set.start_time);
	while (now - start < stop)
	{
		now = get_time(time_set.start_time);
		usleep(1);
	}
}
