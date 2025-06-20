/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/08 13:15:20 by aobshatk         ###   ########.fr       */
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
		if (now - temp->philo_set.last_eat >= temp->philo_set.time_set.time_to_die)
		{
			sem_post(temp->philo_set.semaphors.sem_alive);
			sem_post(temp->philo_set.semaphors.sem_fork);
			sem_close(temp->philo_set.semaphors.sem_alive);
			sem_close(temp->philo_set.semaphors.sem_fork);
			exit(EXIT_SUCCESS);
		}
		if (temp->philo_set.num_eaten == temp->philo_set.time_set.num_of_eats)
		{
			sem_post(temp->philo_set.semaphors.sem_alive);
			return (NULL);
		}
		sem_post(temp->philo_set.semaphors.sem_alive);
		usleep(1);
	}
	return (NULL);
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

int	eaten_enough(t_philo *philo)
{
	sem_wait(philo->philo_set.semaphors.sem_alive);
	if (philo->philo_set.num_eaten == philo->philo_set.time_set.num_of_eats)
	{
		sem_post(philo->philo_set.semaphors.sem_fork);
		sem_post(philo->philo_set.semaphors.sem_alive);
		usleep(2000);
		return (1);
	}
	sem_post(philo->philo_set.semaphors.sem_alive);
	return (0);
}
