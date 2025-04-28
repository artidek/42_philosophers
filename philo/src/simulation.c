/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/28 17:24:59 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_philo	*parse_philos(t_philo *philo)
{
	long int	l_eat;
	long int	time_d;
	long int	cur;

	time_d = philo->time_set.time_to_die;
	cur = get_stop_time();
	while (philo)
	{
		pthread_mutex_lock(philo->eat_lock);
		l_eat = (*philo->last_eat);
		pthread_mutex_unlock(philo->eat_lock);
		if (l_eat > 0 && absl(l_eat - cur) > (time_d + 8))
		{
			message(philo, 4, get_time());
			return (philo);
		}
		philo = philo->next;
	}
	return (NULL);
}

void	check_death_timer(void *philo)
{
	t_philo	*temp;
	t_philo	*death_philo;

	temp = (t_philo *)philo;
	while (1)
	{
		death_philo = parse_philos(temp);
		if (death_philo)
		{
			pthread_mutex_lock(death_philo->alive_lock);
			*(death_philo->sim_stop) = 1;
			pthread_mutex_unlock(death_philo->alive_lock);
			return ;
		}
	}
}

static void	init_mutexes(t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		temp->prev->fork_lock = malloc(sizeof(pthread_mutex_t));
		temp->eat_lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(temp->prev->fork_lock, NULL);
		pthread_mutex_init(temp->eat_lock, NULL);
		temp = temp->next;
	}
}

static void	sim_multiple(t_philo *philos)
{
	t_philo			*temp;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	m_lock;

	temp = philos;
	pthread_mutex_init(&stop_lock, NULL);
	pthread_mutex_init(&m_lock, NULL);
	init_mutexes(temp);
	while (temp)
	{
		temp->alive_lock = &stop_lock;
		temp->message_lock = &m_lock;
		(*temp->last_eat) = get_stop_time();
		pthread_create(&(temp->thrd_philo), NULL, sim_philos, temp);
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

void	start_sim(t_philo *philos)
{
	if (philos->next)
		sim_multiple(philos);
	else
		sim_philo(philos);
}
