/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/18 12:29:49 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static int	stop_sim(t_philo *philos)
{
	t_philo *temp;

	temp = philos;
	if (!temp->next)
	{
		if (temp->death)
			return (1);
	}
	else
	{
		while (temp)
		{
			if(temp->death)
			{
				mutex_cleanup(philos);
				return(1);
			}
			temp = temp->next;
		}
	}
	return (0);
}

static void	sim_one (t_philo *philos)
{
	pthread_create(&(philos->thrd_philo), NULL, (philos->one), philos);
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
		gettimeofday(&temp->start, NULL);
		pthread_mutex_init(&(temp->fork_lock), NULL);
		pthread_create(&(temp->thrd_philo), NULL, (temp->multiple), temp);
		pthread_detach(temp->thrd_philo);
		temp = temp->next;
		usleep(500);
	}
	while (!stop_sim(philos))
		usleep(500);
}

void	start_sim (t_philo *philos)
{
	if (philos->next)
		sim_multiple(philos);
	else
		sim_one(philos);
}
