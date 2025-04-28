/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:16 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/28 13:00:31 by aobshatk         ###   ########.fr       */
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

long int	get_stop_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long int	get_time(void)
{
	struct timeval	time_stamp;
	long int		millisecs;

	gettimeofday(&time_stamp, NULL);
	millisecs = time_stamp.tv_usec;
	if (millisecs == 0 || millisecs < 1000)
		return (millisecs);
	else
		return (millisecs / 1000);
}

long int	absl(long int val)
{
	if (val < 0)
		return (-val);
	else
		return (val);
}
