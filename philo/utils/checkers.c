/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:38:19 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/11 16:21:34 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_digit (char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	is_int (char **argv)
{
	int	i;
	long long int	check_val;

	i = 0;
	while (argv[i])
	{
		check_val = ft_atoil(argv[i]);
		if (check_val > INT_MAX || check_val < INT_MIN )
			return (0);
		i++;
	}
	return (1);
}

static int	max_sleep (char **argv)
{
	int	i;
	long long int	limit;

	i = 2;
	while(argv[i])
	{
		limit = ft_atoil(argv[i]);
		if (limit > 1000000)
			return (1);
		if (limit < 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_valid(char **argv)
{
	if (!is_digit(argv))
	{
		printf("Some of the arguments is not a number\n");
		return (0);
	}
	if (!is_int(argv))
	{
		printf("Some of the arguments is not an integer\n");
		return (0);
	}
	if (ft_atoil(argv[1]) < 1)
	{
		printf("Wrong number of philosophers\n");
		return (0);
	}
	if (max_sleep(argv))
	{
		printf("Excided max or min allowed value\n");
		return (0);
	}
	return (1);
}
