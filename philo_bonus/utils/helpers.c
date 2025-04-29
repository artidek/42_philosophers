/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:16 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/29 12:21:15 by aobshatk         ###   ########.fr       */
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

void	clear_philos(t_philo **philos)
{
	t_philo	*next;

	if (!*philos)
		return ;
	while (*philos)
	{
		next = (*philos)->next;
		free((*philos)->last_eat);
		free((*philos)->cur_time);
		free(*philos);
		*philos = next;
	}
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long int	absl(long int val)
{
	if (val < 0)
		return (-val);
	else
		return (val);
}

int	check_death (t_philo *philo)
{
	long int	*c_time;
	long int	*l_eat;
	long int	death_time;

	c_time = philo->cur_time;
	l_eat = philo->last_eat;
	death_time = philo->time_set.time_to_die;
	if (absl(*c_time - *l_eat) > death_time + 8 || philo->num_eaten == philo->time_set.num_of_eats)
		return (1);
	else
		return (0);
}
