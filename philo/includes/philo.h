/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/05 16:21:36 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_time_set
{
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start_time;
	int				num_of_eats;
}					t_time_set;

typedef struct s_philo
{
	int				philo;
	int				*sim_stop;
	int				num_eaten;
	long int		*last_eat;
	pthread_t		thrd_philo;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*alive_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*message_lock;
	t_time_set		time_set;
	void			(*lock)(struct s_philo *);
	void			*(*multiple)(void *);
	void			*(*one)(void *);
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

int					check_valid(char **argv);
long int			time_diff(struct timeval start);
long int			get_time(long int start_time);
long int			absl(long int val);
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv);
void				message(t_philo *philo, int msg, long int timestamp);
void				start_sim(t_philo *philos);
void				clear_philos(t_philo **philos);
void				lock(t_philo *philo);
void				unlock(t_philo *philo);
void				mutex_cleanup(t_philo *philos);
void				check_death_timer(void *philo);
void				philo_delay(t_philo *philo, long int delay);
void				destroy_mutexes(t_philo *philos);
void				init_mutexes(t_philo *philos);
void				*sim_philos(void *philos);
void				*sim_philo(void *philos);
int					eat(t_philo *philo);
int					p_sleep(t_philo *philo);
int					everybody_eaten(t_philo *philo);
#endif
