/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/12 23:10:28 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_time_set
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_thinking;
	int				num_of_eats;
}					t_time_set;

typedef struct s_lock
{
	pthread_mutex_t	death_timer_lock;
	pthread_t		death_timer;
}					t_lock;

typedef struct s_philo
{
	// int				fork;
	// int				hungry;
	int				death;
	int				philo;
	pthread_t		thrd_philo;
	pthread_mutex_t	fork_lock;
	t_time_set		time_set;
	t_lock			death_timer;
	struct s_philo	*prev;
	struct s_philo	*next;

}					t_philo;

int					check_valid(char **argv);
int					check_death(t_philo *philo);
long int			get_time(void);
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv);
void				start_sim(t_philo *philos);
void				clear_philos(t_philo **philos);
void				philo_message(int msg, int philo);
void				lock(t_philo *philo, int select);
void				unlock(t_philo *philo, int select);
#endif
