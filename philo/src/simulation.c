/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/23 20:32:24 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static void	sim_one (t_philo *philos)
{
	pthread_create(&(philos->thrd_philo), NULL, (philos->one), philos);
	pthread_detach(philos->thrd_philo);
}

static void	sim_multiple (t_philo *philos)
{
	t_philo	*temp;
	int	stop_sim;

	temp = philos;
	stop_sim = 0;
	while (temp)
	{
		temp->sim_stop = &stop_sim;
		pthread_mutex_init(&(temp->fork_lock), NULL);
		pthread_create(&(temp->thrd_philo), NULL, (temp->multiple), temp);
		temp = temp->next;
		usleep(500);
	}
	temp = philos;
	while (temp)
	{
		pthread_join(philos->thrd_philo, NULL);
		temp = temp->next;
	}
}

void	start_sim (t_philo *philos)
{
	if (philos->next)
		sim_multiple(philos);
	else
		sim_one(philos);
}
