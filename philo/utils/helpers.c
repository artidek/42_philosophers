/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:16 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/15 14:31:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

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
	t_philo *next;

	if (!*philos)
		return;
	while(*philos)
	{
		next = (*philos)->next;
		free(*philos);
		*philos = next;
	}
}

long int	get_time ()
{
	struct timeval dt;

	gettimeofday(&dt, NULL);
	return (dt.tv_usec);
}

long int	time_diff(struct timeval start)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	if (start.tv_sec - current.tv_sec > 0)
		return((1000000 + current.tv_usec) - start.tv_usec);
	else
		return (current.tv_usec - start.tv_usec);
}
