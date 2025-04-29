/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/29 12:18:02 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	eat(t_philo *philo)
{
	if (check_death(philo))
		return (0);
	sem_wait(philo->sem_fork);
	if (check_death(philo))
		return (0);
	printf("%ld %d has taken a fork\n", get_time(), philo->philo);
	sem_wait(philo->sem_fork);
	if (check_death(philo))
		return (0);
	printf("%ld %d has taken a fork\n", get_time(), philo->philo);
	usleep(500);
	if (check_death(philo))
		return (0);
	printf("%ld %d is eating\n", get_time(), philo->philo);
	usleep(philo->time_set.time_to_eat);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
	return (1);
}

static void	p_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time(), philo->philo);
	usleep(philo->time_set.time_to_sleep);
}

static void	sim_philo(t_philo *philo)
{
	while (1)
	{
		(*philo->cur_time) = get_time();
		if (check_death(philo))
		{
			printf("%ld %d died\n", get_time(), philo->philo);
			return ;
		}
		printf("%ld %d is thinking\n", get_time(), philo->philo);
		usleep(1000);
		if (!eat(philo))
		{
			printf("%ld %d died\n", get_time(), philo->philo);
			return ;
		}
		(*philo->last_eat) = get_time();
		philo->num_eaten += 1;
		if (check_death(philo))
		{
			printf("%ld %d died\n", get_time(), philo->philo);
			return ;
		}
		p_sleep(philo);
	}
}

static void	sim_philos(t_philo *philos)
{
	t_philo	*temp;
	pid_t	pid;
	pid_t	exit_pid;

	temp = philos;
	while (temp)
	{
		pid = fork();
		if (pid == 0)
		{
			(*temp->last_eat) = get_time();
			sim_philo(temp);
			return ;
		}
		else if (pid > 0)
		{
			temp->pid = pid;
			temp = temp->next;
		}
		usleep(1000);
	}
	exit_pid = check_proc_stat();
	kill_ghosts(philos, exit_pid);
}

void	start_sim(t_philo *philos)
{
	if (philos->next)
		sim_philos(philos);
	else
	{
		printf("%ld %d is thinking\n", get_time(), philos->philo);
		usleep(philos->time_set.time_to_eat);
		printf("%ld %d died", get_time(), philos->philo);
	}
}
