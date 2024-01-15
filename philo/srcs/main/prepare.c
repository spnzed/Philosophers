/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:12:47 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, long philo_nbr)
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

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_position = i;
		table->philos[i].philo_id = i + 1;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].limit_meals_nbr = table->limit_meals_nbr;
		table->philos[i].meals_count = 0;
		table->philos[i].eating = false;
		table->forks[i].fork_id = i;
		if (!(ft_safe_mutex(&table->philos[i].mutex, INIT)))
			return (1);
		assign_forks(&table->philos[i], table->forks, table->philo_nbr);
		i++;
	}
	return (0);
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (i++ < table->philo_nbr)
	{
		if (!(ft_safe_mutex(&table->forks[i].fork, INIT)))
			return (ft_error("Error while creating forks"));
		if (!(ft_safe_mutex(&table->philos[i].mutex, INIT)))
			return (ft_error("Error while creating philos"));
	}
	return (0);
}

static int	init_malloc(t_table *table)
{
	table->threads = malloc(table->philo_nbr * sizeof(t_thread));
	if (!table->threads)
		return (ft_error("Error while allocating threads"));
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (!table->forks)
		return (ft_error("Error while allocating forks"));
	table->philos = malloc((table->philo_nbr) * sizeof(t_philo));
	if (!table->philos)
		return (ft_error("Error while allocating philos"));
	return (0);
}

int	prepare_table(t_table *table)
{
	if (init_malloc(table))
		return (1);
	if (init_mutex(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}
