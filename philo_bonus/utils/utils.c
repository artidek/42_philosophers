/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:14:56 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/08 13:15:34 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo_bonus.h"

static int	find_philo_by_pid(t_philo *philo, pid_t exit_pid)
{
	while (philo)
	{
		if (philo->pid == exit_pid)
			return (philo->philo_set.philo);
		philo = philo->next;
	}
	return (0);
}

pid_t	check_proc_stat(t_philo *philo)
{
	pid_t	exit_pid;
	int		status;

	exit_pid = 0;
	while (1)
	{
		exit_pid = waitpid(-1, &status, 0);
		if (exit_pid < 1)
			return (-1);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_SUCCESS)
			{
				message(find_philo_by_pid(philo, exit_pid),
					philo->philo_set.time_set.start_time, 4);
				return (exit_pid);
			}
		}
		usleep(10);
	}
	return (exit_pid);
}

void	kill_ghosts(t_philo *philos)
{
	while (philos)
	{
		kill(philos->pid, SIGKILL);
		philos = philos->next;
	}
}

void	init_semaphors(t_semaphors *semaphors, int num_philos)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_ALLIVE);
	semaphors->sem_fork = sem_open(SEM_FORK, O_CREAT|O_EXCL, 0644, num_philos);
	semaphors->sem_alive = sem_open(SEM_ALLIVE, O_CREAT|O_EXCL, 0644, 1);
}
