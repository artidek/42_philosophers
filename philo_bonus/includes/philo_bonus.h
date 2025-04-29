/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:42:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/29 12:06:07 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <sys/types.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef SEM_FORK
#  define SEM_FORK "sem_fork"
# endif

typedef struct s_time_set
{
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				num_of_eats;
}					t_time_set;

typedef struct s_philo
{
	int				philo;
	int				num_eaten;
	pid_t			pid;
	long int		*cur_time;
	long int		*last_eat;
	sem_t			*sem_fork;
	t_time_set		time_set;
	struct s_philo	*next;
}					t_philo;

int					check_valid(char **argv);
int					check_death(t_philo *philo);
long int			time_diff(struct timeval start);
long int			get_time(void);
long int			absl(long int val);
long long int		ft_atoil(const char *str);
void				init_philos(t_time_set *time_set, t_philo **philos,
						char **argv);
void				start_sim(t_philo *philos);
void				kill_ghosts(t_philo *philos, pid_t exit_pid);
void				clear_philos(t_philo **philos);
char				*gen_sem_name(int len);
pid_t				check_proc_stat();
#endif
