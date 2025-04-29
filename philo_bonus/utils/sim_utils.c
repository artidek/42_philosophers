/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/29 12:00:08 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

pid_t	check_proc_stat()
{
	pid_t	exit_pid;

	exit_pid = 0;
	while (1)
	{
		exit_pid = waitpid(-1, NULL, 0);
		if (exit_pid > 0)
			return (exit_pid);
		else if (exit_pid == -1)
		{
			perror("waitpid failed");
			return (-1);
		}
	}
	return (exit_pid); 
}

void	kill_ghosts(t_philo *philos, pid_t exit_pid)
{
	while (philos)
	{
		if (philos->pid != exit_pid)
			kill(philos->pid, SIGKILL);
		philos = philos->next;
	}
}
