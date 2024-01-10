/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/10 18:00:39 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
***One Philo***
./philo 1 800 200 200

***No philo dies***
./philo 5 800 200 200
./philo 4 410 200 200
*/

/*
TODO
***Philo dies***
./philo 4 310 200 100

***No Philo dies***
./philo 5 800 200 200 7
*/

void	clean_dishes(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	table = NULL;
	while (i < table->philo_nbr)
	{
		philo = &table->philos[i];
		ft_safe_mutex(&philo->mutex, DESTROY);
		fork = philo->left;
		if (fork)
			ft_safe_mutex(&philo->left->fork, DESTROY);
		fork = philo->right;
		if (fork)
			ft_safe_mutex(&philo->right->fork, DESTROY);
		i++;
	}
	ft_safe_mutex(&table->write, DESTROY);
	ft_safe_mutex(&table->mutex, DESTROY);
	free(table->forks);
	free(table->philos);
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
