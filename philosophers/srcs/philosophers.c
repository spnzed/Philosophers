/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/12 16:39:44 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
***No philo dies***
./philo 5 800 200 200		✅
./philo 4 410 200 200		✅
***Philo dies***
./philo 4 310 200 100		✅
*/

/*
***One Philo***
./philo 1 800 200 200		✅
***No Philo dies***
./philo 5 800 200 200 7		✅????
*/

static void	clean_table(t_table	*table)
{
	if (table->threads)
		free(table->threads);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

void	clean_dishes(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		ft_safe_mutex(&table->forks[i].fork, DESTROY);
		ft_safe_mutex(&table->philos[i].mutex, DESTROY);
		i++;
	}
	ft_safe_mutex(&table->write, DESTROY);
	ft_safe_mutex(&table->mutex, DESTROY);
	clean_table(table);
}

int	main (int argc , char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv))
			return (0);
		if (prepare_table(&table))
		{
			clean_dishes(&table);
			return(ft_error("Table can't be prepared.\n"));
		}
		if (table.philo_nbr == 1)
			return (one_philo(&table));
		if (start_dinning(&table))
		{
			clean_dishes(&table);
			return(ft_error("Dinner interrupted.\n"));
		}
	}
	else
		return (ft_error("Input isn't the correct one.\n" 
			GREEN"Example: ./philo 5 800 800 500\n"RESET));
}
