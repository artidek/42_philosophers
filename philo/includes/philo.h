/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/11 23:26:07 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_time_set
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_thinking;
	int				num_of_eats;
}					t_time_set;

typedef struct s_philo
{
	int				fork;
	int				hungry;
	int				death;
	int				philo;
	void			(*death_time)(void *);
	void			(*sim)(void *);
	pthread_t		thrd_philo;
	pthread_t		thrd_live;
	pthread_mutex_t	fork_lock;
	t_time_set		time_set;
	struct s_philo	*prev;
	struct s_philo	*next;

}					t_philo;

int					check_valid(char **argv);
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv);
void				sim_philo(void *philos);
void				death_time(void *philo);
#endif
