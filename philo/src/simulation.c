/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/02 23:05:16 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*sim_philo(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	printf("%ld %d is thinking\n", get_time(philos), philo->philo);
	usleep(philo->time_set.time_to_die);
	printf("%ld %d died\n", get_time(philos), philo->philo);
	return (NULL);
}

void	*sim_philos(void *philos)
{
	t_philo	*philo_n;

	philo_n = (t_philo *)philos;
	*(philo_n->last_eat) = get_time(philo_n);
	while (1)
	{
		usleep(250);
		if (check_stop(philo_n, get_time(philo_n)))
			return (NULL);
		if (!message(philo_n, PHILO_THINKING, check_stop(philo_n, get_time(philo_n))))
			return (NULL);
		philo_delay(philo_n, 2);
		if (!go_eat(philo_n))
			return (NULL);
		philo_n->num_eaten += 1;
		if (!go_sleep(philo_n))
			return (NULL);
		if (philo_n->time_set.num_of_eats == philo_n->num_eaten)
			return (NULL);
	}
}

static void	init_mutexes(t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		temp->prev->fork_lock = malloc(sizeof(pthread_mutex_t));
		//temp->eat_lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(temp->prev->fork_lock, NULL);
		//pthread_mutex_init(temp->eat_lock, NULL);
		temp = temp->next;
	}
}

static void	sim_multiple(t_philo *philos)
{
	t_philo			*temp;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	m_lock;
	//long int		start_delay;

	temp = philos;
	pthread_mutex_init(&stop_lock, NULL);
	pthread_mutex_init(&m_lock, NULL);
	init_mutexes(temp);
	while (temp)
	{
		temp->alive_lock = &stop_lock;
		temp->message_lock = &m_lock;
		pthread_create(&(temp->thrd_philo), NULL, sim_philos, temp);
		temp = temp->next;
	}
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
