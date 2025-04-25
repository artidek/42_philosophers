/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/25 16:20:32 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	check_death_timer(void *philo)
{
	t_philo	*temp;

	while (1)
	{
		usleep(1000);
		temp = philo;
		while (temp)
		{
			pthread_mutex_lock(&temp->alive_lock);
			if (get_stop_time() - temp->last_eat >= temp->time_set.time_to_die / 1000)
			{
				usleep(500);
				printf("%ld %d died\n", get_time(), temp->philo);
				*(temp->sim_stop) = 1;
				pthread_mutex_unlock(&temp->alive_lock);
				return;
			}
			pthread_mutex_unlock(&temp->alive_lock);
			temp = temp->next;
		}
	}
}

static void	sim_one (t_philo *philos)
{
	pthread_create(&(philos->thrd_philo), NULL, (philos->one), philos);
	pthread_join(philos->thrd_philo, NULL);
}

static void	sim_multiple (t_philo *philos)
{
	t_philo	*temp;
	pthread_mutex_t stop_lock;
	int	stop_sim;

	temp = philos;
	stop_sim = 0;
	pthread_mutex_init(&stop_lock, NULL);
	while (temp)
	{
		temp->sim_stop = &stop_sim;
		temp->alive_lock = stop_lock;
		temp->last_eat = get_stop_time();
		pthread_mutex_init(&(temp->fork_lock), NULL);
		pthread_create(&(temp->thrd_philo), NULL, (temp->multiple), temp);
		temp = temp->next;
	}
	check_death_timer(philos);
	temp = philos;
	while (temp)
	{
		pthread_join(temp->thrd_philo, NULL);
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
