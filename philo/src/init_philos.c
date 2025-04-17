/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:39:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/17 14:45:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_time(char **argv, t_time_set *time_set)
{
	time_set->time_to_die = (long int)ft_atoil(argv[2]);
	time_set->time_to_eat = (long int)ft_atoil(argv[3]);
	time_set->time_to_sleep = (long int)ft_atoil(argv[4]);
	if (!argv[5])
		time_set->num_of_eats = 0;
	else
		time_set->num_of_eats = (int)ft_atoil(argv[5]);
}

static t_philo	*last_philo(t_philo *philos)
{
	if (!philos)
		return (NULL);
	if (!philos->next)
		return (philos);
	while (philos->next)
		philos = philos->next;
	return (philos);
}

static t_philo	*new_philo(t_time_set time_set, int philo)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->death = 0;
	new_philo->stop_timer = 0;
	new_philo->philo = philo;
	new_philo->time_set = time_set;
	new_philo->lock = lock;
	new_philo->unlock = unlock;
	new_philo->message = philo_message;
	new_philo->diff = time_diff;
	new_philo->multiple = sim_philos;
	new_philo->one = sim_philo;
	new_philo->eat_m = go_eat_m;
	new_philo->eat_o = go_eat_o;
	new_philo->sleep = go_sleep;
	new_philo->death_timer = check_death_timer;
	new_philo->prev = NULL;
	new_philo->next = NULL;
	return (new_philo);
}

static void	add_philo(t_philo **philos, t_philo *new_philo)
{
	t_philo	*lst_philo;

	if (!philos)
		return ;
	if (!new_philo && *philos)
	{
		free(philos);
		return ;
	}
	if (!*philos)
	{
		*philos = new_philo;
		return ;
	}
	lst_philo = last_philo(*philos);
	lst_philo->next = new_philo;
	new_philo->prev = lst_philo;
}

void	init_philos(t_time_set *time_set, t_philo **philos, char **argv)
{
	int	num_philos;
	int	i;

	num_philos = (int)ft_atoil(argv[1]);
	i = 0;
	set_time(argv, time_set);
	while (i < num_philos)
	{
		add_philo(philos, new_philo(*time_set, i + 1));
		i++;
	}
	if (*philos && (*philos)->next)
		(*philos)->prev = last_philo(*philos);
}
