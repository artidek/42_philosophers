/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/16 18:17:13 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static int	stop_sim(t_philo *philos)
{
	if (!philos->next)
	{
		if (philos->death)
			return (1);
	}
	else
	{
		while (philos)
		{
			if(philos->death)
				return (1);
			philos = philos->next;
		}
	}
	return (0);
}

static void	sim_one (t_philo *philos)
{
	pthread_create(&(philos->thrd_philo), NULL, &sim_philo, philos);
	pthread_detach(philos->thrd_philo);
	while (!stop_sim(philos))
		usleep(1000);
}

static void	sim_multiple (t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		pthread_mutex_init(&(temp->fork_lock), NULL);
		pthread_create(&(temp->thrd_philo), NULL, sim_philos, temp);
		pthread_detach(temp->thrd_philo);
		temp = temp->next;
	}
	while (!stop_sim(philos))
		usleep(100);
}

void	start_sim (t_philo *philos)
{
	if (philos->next)
		sim_multiple(philos);
	else
		sim_one(philos);
}
