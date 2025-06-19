/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/08 13:16:58 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORK "sem_fork"
# define SEM_ALLIVE "sem_alive"

typedef struct s_time_set
{
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start_time;
	int				num_of_eats;
}					t_time_set;

typedef struct s_semaphors
{
	sem_t			*sem_fork;
	sem_t			*sem_alive;
}					t_semaphors;

typedef struct s_philo_set
{
	int				philo;
	int				num_eaten;
	long int		last_eat;
	t_time_set		time_set;
	t_semaphors		semaphors;
	pthread_t		check_death;
}					t_philo_set;

typedef struct s_philo
{
	pid_t			pid;
	t_philo_set		philo_set;
	struct s_philo	*head;
	struct s_philo	*next;
}					t_philo;

int					check_valid(char **argv);
int					message(int philo, long int start_time, int msg);
int				eaten_enough(t_philo *philo);
long int			time_diff(struct timeval start);
long int			get_time(long int start_time);
long int			absl(long int val);
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv, t_semaphors *semaphors);
void				start_sim(t_philo *philos);
void				kill_ghosts(t_philo *philos);
void				clear_philos(t_philo **philos);
void				philo_delay(t_time_set time_set, long int stop);
void				init_semaphors(t_semaphors *semaphors, int num_philos);
void				*check_death(void *philo);
pid_t				check_proc_stat(t_philo *philo);
#endif
