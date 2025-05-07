/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:01:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/02 23:02:12 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	go_eat(t_philo *philo)
{
	lock(philo);
	usleep (250);
	if (!message(philo, FORK_TAKEN, check_stop(philo, get_time(philo))))
		return (0);
	usleep(250);
	if (!message(philo, FORK_TAKEN, check_stop(philo, get_time(philo))))
		return (0);
	usleep (250);
	if (!message(philo, PHILO_EATING, check_stop(philo, get_time(philo))))
		return (0);
	*(philo->last_eat) = get_time(philo);
	philo_delay(philo, philo->time_set.time_to_eat);
	if (check_stop(philo, get_time(philo)))
	{
		unlock(philo);
		return (0);
	}
	unlock(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	if (!message(philo, PHILO_SLEEPING, check_stop(philo, get_time(philo))))
		return (0);
	if (check_stop(philo, get_time(philo)))
		return (0);
	philo_delay(philo, philo->time_set.time_to_sleep);
	if (check_stop(philo, get_time(philo)))
		return (0);
	return (1);
}
