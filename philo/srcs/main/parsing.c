/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2024/01/17 15:21:00 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	error_syntax(char *num)
{
	int	i;

	i = 0;
	if (!(num[0] >= '0' && num[0] <= '9'))
		return (1);
	while (num[i])
	{
		if (i == 0 && !((num[i] >= '0' && num[i] <= '9')))
			return (1);
		else if (i != 0 && !(num[i] >= '0' && num[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	comprove_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			return (ft_error("Invalid input please put numbers"));
		if (ft_atol(argv[i]) > INT_MAX)
			return (ft_error ("INT MAX is the limit sweetie"));
		i++;
	}
	return (0);
}

int	parse_input(t_table *table, char **argv)
{
	if (comprove_argv (argv))
		return (1);
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->limit_meals_nbr = ft_atoi(argv[5]);
	else
		table->limit_meals_nbr = -1;
	if (table->philo_nbr <= 0 || table->philo_nbr > 200
		|| table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (ft_error("Invalid input values"));
	table->start_simulation = 0;
	table->full_philos = 0;
	if (!(ft_safe_mutex(&table->mutex, INIT)))
		return (1);
	if (!(ft_safe_mutex(&table->write, INIT)))
		return (1);
	return (0);
}
