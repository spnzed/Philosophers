/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/13 17:53:54 by aaespino         ###   ########.fr       */
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
	philo->dead = false;
	philo->philo_position = i;
	philo->philo_id = i + 1;
	philo->philo_mutex = &philo->table->table_mutex;
	philo->write_mutex = &philo->table->write_mutex;
	assign_forks(philo, forks, nbr);
}

static void	assign_table_data(t_philo *philo, t_data *data)
{
	philo->data->philo_nbr = data->philo_nbr;
	philo->data->time_to_die = data->time_to_die;
	philo->data->time_to_eat = data->time_to_eat;
	philo->data->time_to_sleep = data->time_to_sleep;
	philo->data->limit_meals_nbr = data->limit_meals_nbr;
	philo->data->start_simulation = 0;
	philo->data->last_meal_time = 0;
	philo->data->threads_running = 0;
}

static bool	init_mutex(t_table *table, t_data *data)
{
	int i;

	i = 0;
	if (!(ft_safe_mutex(&table->table_mutex, INIT)))
    	return (NULL);	
	if (!(ft_safe_mutex(&table->write_mutex, INIT)))
    	return (NULL);
	while (i < data->philo_nbr)
	{
		if (!(ft_safe_mutex(&table->forks[i].fork, INIT)))
        	return (NULL);
		i++;
	}
	return (true);
}

static bool	init_malloc(t_table *table, t_data *data)
{
	table->philos = malloc(data->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (NULL);
	table->forks = malloc(data->philo_nbr * sizeof(t_fork));
	if (!table->forks)
		return (NULL);
	return (true);
}

bool	prepare_table(t_table *table, t_data *data)
{
	int i;
	long nbr;

	i = 0;
	nbr = data->philo_nbr;
	if (!(init_malloc(table, data)))
		return (NULL);
	if (!(init_mutex(table, data)))
		return (NULL);
	while (i < nbr)
	{
		table->philos[i].data = malloc(sizeof(t_data));
		if (!table->philos[i].data)
			return (NULL);
		assign_table_data(&table->philos[i], data);
		table->forks[i].fork_id = i;
		table->philos[i].table = table;
		prepare_philos(&table->philos[i], table->forks, i, nbr);
		i++;
	}
	return (true);
}
