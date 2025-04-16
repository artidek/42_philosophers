/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/16 23:23:01 by aobshatk         ###   ########.fr       */
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
# include <string.h>

typedef struct s_time_set
{
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				num_of_eats;
}					t_time_set;

typedef struct s_philo
{
	int				death;
	int				philo;
	pthread_t		thrd_philo;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	alive_lock;
	t_time_set		time_set;
	void			(*lock)(struct s_philo *);
	void			(*unlock)(struct s_philo *);
	void			(*message)(int msg, struct s_philo *);
	long int		(*diff)(struct timeval start);
	struct s_philo	*prev;
	struct s_philo	*next;

}					t_philo;

int					check_valid(char **argv);
int					check_death(t_philo *philo);
long int			time_diff(struct timeval start);
long int				get_time();
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv);
void				start_sim(t_philo *philos);
void				clear_philos(t_philo **philos);
void				philo_message(int msg, t_philo *philo);
void				lock(t_philo *philo);
void				unlock(t_philo *philo);
void				*sim_philos(void *philos);
void				*sim_philo(void *philos);
int					go_eat_m(t_philo *philo);
int					go_sleep(t_philo *philo);
int					go_eat_o(t_philo *philo);
#endif
