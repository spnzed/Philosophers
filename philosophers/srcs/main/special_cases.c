/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:28:24 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/22 19:09:20 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	philo->data->start_simulation = ft_get_time();
	philo_does(THINK, philo);
	print_action(philo, YELLOW"has taken a fork \t [🍴]");
	dead(philo);
	return (NULL);
}

bool	simulation_finished(t_table *table)
{
	return (safe_get_bool(&table->table_mutex, &table->end));
}

bool philo_is_full(t_philo *philo)
{
	return (safe_get_bool(philo->philo_mutex, &philo->full));
}

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
	long	last_meal;

	if (safe_get_bool(philo->philo_mutex, &philo->full))
		return (NULL);
	time = ft_get_time();
	last_meal = safe_get_long(&philo->table->table_mutex, philo->data->last_meal_time);
	if (last_meal > 0)
		time -= last_meal;
	else 
		return (NULL);
	time_to_die = safe_get_long(philo->philo_mutex, philo->data->time_to_die);
	if (time >= time_to_die)
	{
		dead(philo);
		return (true);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	t_table *table;;
	long 	time_to_die;
	long 	nbr;
	long	threads;
	int		i;

	table = (t_table *)data;
	time_to_die = safe_get_long(table->philos->philo_mutex, table->philos->data->time_to_die);
	nbr = safe_get_long(table->philos->philo_mutex, table->philos->data->philo_nbr);
	threads = safe_get_long(table->philos->philo_mutex, table->philos->data->threads_running);
	i = 0;
	while (!all_threads(&table->table_mutex, &threads, nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < nbr && !simulation_finished(table))
		{
			if (philo_died(&table->philos[i]))
				safe_put_bool(&table->table_mutex, &table->end, true);
			i++;
		}
	}
	return (NULL);
}
