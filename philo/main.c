/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:56:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/11 23:30:41 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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
	init_philos(&time_set, &philos, argv);
	if (!philos)
		return (1);
	//start_sim(philos);
	free(philos);
	return (0);
}
