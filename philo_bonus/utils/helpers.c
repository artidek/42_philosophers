/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:16 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/07 12:18:56 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

long int	get_time(long int start_time)
{
	struct timeval	time;
	long int		time_extract;

	gettimeofday(&time, NULL);
	time_extract = ((time.tv_sec - start_time) * 1000) + (time.tv_usec / 1000);
	return (time_extract);
}

long int	absl(long int val)
{
	if (val < 0)
		return (-val);
	else
		return (val);
}

void	clear_philos(t_philo **philos)
{
	t_philo	*temp;

	while (*philos)
	{
		temp = (*philos)->next;
		free(*philos);
		*philos = temp;
	}
}
