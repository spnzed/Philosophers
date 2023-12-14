/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:28:24 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/14 20:04:26 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *pointer)
{
	t_philo	*philo;
	bool	simulation;

	simulation = false;
	philo = (t_philo *)pointer;
	philo->data->start_simulation = ft_get_time();
	safe_put_long(philo->philo_mutex, &philo->data->last_meal_time, ft_get_time());
	safe_increase_long(&philo->table->table_mutex, &philo->table->table_data->threads_running);
	print_action(philo, YELLOW"has taken a fork \t [🍴]");
	while (!simulation)
	{
		simulation = safe_get_bool(&philo->table->table_mutex, &philo->table->end_simu);
		ft_usleep(20);
		safe_put_bool (&philo->table->table_mutex, &philo->table->end_simu, true);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	t_table *table;
	bool	full;
	long 	nbr;
	long 	time_to_die;
	long 	time;
	int		i;

	table = (t_table *)data;
	full = false;
	nbr = safe_get_long(&table->table_mutex, table->table_data->philo_nbr);
	time_to_die = safe_get_long(&table->table_mutex, table->table_data->time_to_die);
	while (!full)
	{
		i = 0;
		while (i < nbr)
		{
			time = safe_get_long(&table->table_mutex, table->table_data->last_meal_time);
			if (time > time_to_die)
			{
				dead(&table->philos[i]);
				return (NULL);
			}
		}
		full = safe_get_bool(&table->table_mutex, &table->philos->full);
	}
	return (NULL);
}
