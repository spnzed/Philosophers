/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:28:24 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/05 17:36:46 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool all_threads(t_mutex	*mutex, long *threads, long philo_nbr)
{
	bool ret;

	ret = false;
	ft_safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	ft_safe_mutex(mutex, UNLOCK);
	return (true);
}

static bool philo_died(t_philo *philo)
{
	long 	time;
	long	time_to_die;

	if (safe_get_bool(&philo->mutex, &philo->full))
		return (NULL);
	time = ft_get_time() - safe_get_long(&philo->mutex, philo->last_meal_time);
	time_to_die = philo->table->time_to_die;
	if (time > time_to_die)
		return (true);
	return (NULL);
}

void	*monitor(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	i = 0;
	while (!all_threads(&table->table_mutex,
			&table->threads_running, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(&table->philos[i]))
			{
				safe_put_bool(&table->table_mutex, &table->end, true);
				philo_does(DIE, &table->philos[i]);
			}
			i++;
		}
	}
	return (NULL);
}

void	*one_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	philo->table->start_simulation = ft_get_time();
	do_think(philo);
	philo_does(DIE, philo);
	return (NULL);
}
