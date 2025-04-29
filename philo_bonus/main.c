/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:56:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/29 11:56:12 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_time_set	time_set;
	t_philo	*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (!check_valid(argv))
		return (1);
	if (argc == 6 && ft_atoil(argv[5]) < 1)
	{
		printf("Invalid number of eats\n");
		return (1);
	}
	init_philos(&time_set, &philos, argv);
	if (!philos)
		return (1);
	start_sim(philos);
	sem_close(philos->sem_fork);
	clear_philos(&philos);
	return (0);
}
