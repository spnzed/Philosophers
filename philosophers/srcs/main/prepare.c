/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/19 20:48:57 by aaespino         ###   ########.fr       */
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

static void	prepare_philos(t_philo *philo, t_fork *forks, int i, long nbr)
{
	philo->meals_count = 0;
	philo->full = false;
	philo->philo_position = i;
	philo->philo_id = i + 1;
	philo->philo_mutex = &philo->table->table_mutex;
	philo->write_mutex = &philo->table->write_mutex;
	assign_forks(philo, forks, nbr);
}

bool	prepare_table(t_table *table, t_data *data)
{
	int i;
	long nbr;

	i = 0;
	nbr = data->philo_nbr;
	table->philo_nbr = data->philo_nbr;
	if (!(init_malloc(table, data)))
		return (NULL);
	if (!(init_mutex(table, data)))
		return (NULL);
	while (i < nbr)
	{
		table->forks[i].fork_id = i;
		table->philos[i].table = table;
		table->philos[i].data = malloc(sizeof(t_data));
		if (!table->philos[i].data)
			return (NULL);
		prepare_philos(&table->philos[i], table->forks, i, nbr);
		assign_table_data(&table->philos[i], data);
		i++;
	}
	return (true);
}
