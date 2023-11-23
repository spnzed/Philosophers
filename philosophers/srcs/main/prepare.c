/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/23 16:13:30 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_forks(t_philo *philo, t_fork *fork, long philo_nbr)
{
	if (philo->philo_position % 2 == 0)
	{
		philo->left = &fork[philo->philo_position];
		philo->right = &fork[(philo->philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->left = &fork[(philo->philo_position + 1) % philo_nbr];
		philo->right = &fork[philo->philo_position];
	}
}

static void	prepare_philos(t_philo *philo, t_fork *forks, int i)
{
	philo->data->meals_count = 0;
	philo->full = false;
	philo->philo_position = i;
	philo->philo_id = i + 1;
	assign_forks(&philo[i], forks, philo->data->philo_nbr);
}

bool	prepare_table(t_table *table, t_data *data)
{
	int i;

	i = 0;
	table->philos = malloc(data->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (false);
	table->forks = malloc(data->philo_nbr * sizeof(t_fork));
	if (!table->forks)
		return (false);
	while (i < data->philo_nbr)
	{
		if (!(ft_safe_mutex(&table->forks[i].fork, INIT)))
        	return (false);
		table->forks[i].fork_id = i;
		table->philos[i].table = table;
		prepare_philos(&table->philos[i], &table->forks[i], i);
		i++;
	}
	return (true);
}
