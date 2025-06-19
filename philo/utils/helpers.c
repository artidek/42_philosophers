/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:16 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 16:06:19 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	ft_atoil(const char *str)
{
	long long int	i;
	long long int	sign;

	i = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = 44 - *str;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	return (i * sign);
}

void	clear_philos(t_philo **philos)
{
	t_philo	*next;

	if (!*philos)
		return ;
	free((*philos)->alive_lock);
	free((*philos)->message_lock);
	while (*philos)
	{
		next = (*philos)->next;
		free((*philos)->fork_lock);
		free((*philos)->eat_lock);
		free((*philos)->last_eat);
		free(*philos);
		*philos = next;
	}
}

long int	get_time(long int start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec - start_time) * 1000) + (time.tv_usec / 1000));
}

long int	absl(long int val)
{
	if (val < 0)
		return (-val);
	else
		return (val);
}

void	destroy_mutexes(t_philo *philos)
{
	pthread_mutex_destroy(philos->alive_lock);
	pthread_mutex_destroy(philos->message_lock);
	while (philos)
	{
		pthread_mutex_destroy(philos->fork_lock);
		pthread_mutex_destroy(philos->eat_lock);
		philos = philos->next;
	}
}
