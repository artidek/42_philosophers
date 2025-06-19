/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/08 12:45:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->philo_set.semaphors.sem_fork);
	sem_wait(philo->philo_set.semaphors.sem_fork);
	message(philo->philo_set.philo, philo->philo_set.time_set.start_time, 1);
	message(philo->philo_set.philo, philo->philo_set.time_set.start_time, 1);
	message(philo->philo_set.philo, philo->philo_set.time_set.start_time, 2);
	sem_wait(philo->philo_set.semaphors.sem_alive);
	philo->philo_set.last_eat = get_time(philo->philo_set.time_set.start_time);
	sem_post(philo->philo_set.semaphors.sem_alive);
	philo_delay(philo->philo_set.time_set, philo->philo_set.time_set.time_to_eat);
	sem_post(philo->philo_set.semaphors.sem_fork);
	sem_post(philo->philo_set.semaphors.sem_fork);
}

static void	p_sleep(t_philo *philo)
{
	message(philo->philo_set.philo, philo->philo_set.time_set.start_time, 3);
	philo_delay(philo->philo_set.time_set, philo->philo_set.time_set.time_to_sleep);
}

static void	run_philo(t_philo *philo)
{
	philo->philo_set.last_eat = get_time(philo->philo_set.time_set.start_time);
	pthread_create(&(philo->philo_set.check_death), NULL, check_death, philo);
	pthread_detach((philo->philo_set.check_death));
	while (1)
	{
		message(philo->philo_set.philo, philo->philo_set.time_set.start_time, 0);
		philo_delay(philo->philo_set.time_set, 1);
		eat(philo);
		philo->philo_set.num_eaten += 1;
		if (eaten_enough(philo))
			return;
		p_sleep(philo);
	}
}

static void	sim_philos(t_philo *philos)
{
	t_philo	*temp;
	pid_t	pid;

	temp = philos;
	while (temp)
	{
		pid = fork();
		if (pid == 0)
		{
			run_philo(temp);
			sem_close(temp->philo_set.semaphors.sem_alive);
			sem_close(temp->philo_set.semaphors.sem_fork);
			return ;
		}
		temp->pid = pid;
		temp = temp->next;
	}
	check_proc_stat(philos);
	kill_ghosts(philos);
}

void	start_sim(t_philo *philos)
{
	if (philos->next)
		sim_philos(philos);
	else
	{
		printf("%ld %d is thinking\n", get_time(philos->philo_set.time_set.start_time), philos->philo_set.philo);
		printf("%ld %d has take a fork\n", get_time(philos->philo_set.time_set.start_time), philos->philo_set.philo);
		philo_delay(philos->philo_set.time_set, philos->philo_set.time_set.time_to_die);
		printf("%ld %d died", get_time(philos->philo_set.time_set.start_time), philos->philo_set.philo);
	}
}
