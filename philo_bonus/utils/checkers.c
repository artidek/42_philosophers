/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:38:19 by aobshatk          #+#    #+#             */
/*   Updated: 2025/04/28 20:05:09 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		check_val = ft_atoil(argv[i]) * 1000;
		if (check_val > INT_MAX || check_val < INT_MIN )
			return (0);
		i++;
	}
	return (1);
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
	if (ft_atoil(argv[2]) < 1 || ft_atoil(argv[3]) < 1 || ft_atoil(argv[4]) < 1)
	{
		printf("Wrong argument\n");
		return (0);
	}
	return (1);
}
