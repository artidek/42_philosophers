/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:39:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 14:30:09 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_time(char **argv, t_time_set *time_set, long int pst)
{
	time_set->time_to_die = (long int)ft_atoil(argv[2]);
	time_set->time_to_eat = (long int)ft_atoil(argv[3]);
	time_set->time_to_sleep = (long int)ft_atoil(argv[4]);
	time_set->start_time = pst;
	if (!argv[5])
		time_set->num_of_eats = -1;
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

static t_philo	*new_philo(t_time_set time_set, int philo, int *stop_sim)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->last_eat = malloc(sizeof(long int));
	(*new_philo->last_eat) = 0;
	new_philo->sim_stop = stop_sim;
	new_philo->philo = philo;
	new_philo->num_eaten = 0;
	new_philo->time_set = time_set;
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
	int				num_philos;
	int				i;
	int				*stop_sim;
	struct timeval	tv;
	int long		prog_start_tm;

	gettimeofday(&tv, NULL);
	prog_start_tm = tv.tv_sec;
	stop_sim = malloc(sizeof(int));
	*stop_sim = 0;
	num_philos = (int)ft_atoil(argv[1]);
	i = 0;
	set_time(argv, time_set, prog_start_tm);
	while (i < num_philos)
	{
		add_philo(philos, new_philo(*time_set, i + 1, stop_sim));
		i++;
	}
	if (*philos && (*philos)->next)
		(*philos)->prev = last_philo(*philos);
}
