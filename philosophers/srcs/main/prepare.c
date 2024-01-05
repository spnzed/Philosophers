/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/04 18:32:06 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_forks(t_philo *philo, t_fork *forks, long philo_nbr)
{
	if (philo->philo_position % 2 == 0)
	{
		philo->left = &forks[philo->philo_position];
		philo->right = &forks[(philo->philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->left = &forks[(philo->philo_position + 1) % philo_nbr];
		philo->right = &forks[philo->philo_position];
	}
}

static bool	prepare_philos(t_philo *philo, t_fork *forks, int i, long nbr)
{
	philo->meals_count = 0;
	philo->full = false;
	philo->philo_position = i;
	philo->philo_id = i + 1;
	if (!(ft_safe_mutex(&philo->mutex, INIT)))
    	return (NULL);	
	assign_forks(philo, forks, nbr);
	return (true);
}

bool	init_mutex(t_table *table)
{
	int i;

	i = 0;
	if (!(ft_safe_mutex(&table->table_mutex, INIT)))
    	return (NULL);	
	if (!(ft_safe_mutex(&table->write_mutex, INIT)))
    	return (NULL);
	while (i < table->philo_nbr)
	{
		if (!(ft_safe_mutex(&table->forks[i].fork, INIT)))
        	return (NULL);
		i++;
	}
	return (true);
}

bool	init_malloc(t_table *table)
{
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (NULL);
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (!table->forks)
		return (NULL);
	return (true);
}


bool	prepare_table(t_table *table)
{
	int i;
	long nbr;

	i = 0;
	nbr = table->philo_nbr;
	if (!(init_malloc(table)))
		return (NULL);
	if (!(init_mutex(table)))
		return (NULL);
	while (i < nbr)
	{
		table->forks[i].fork_id = i;
		table->philos[i].table = table;
		if (!prepare_philos(&table->philos[i], table->forks, i, nbr))
			return (NULL);
		i++;
	}
	return (true);
}
