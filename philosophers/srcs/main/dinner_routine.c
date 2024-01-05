/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/05 18:00:05 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_turns(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		ft_usleep(50);
	else if (philo->philo_id % 2)
		do_think(philo);
}

static void wait_threads(t_table *table)
{
	while (!safe_get_bool(&table->table_mutex, &table->ready))
		;
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	safe_put_long(&philo->mutex, &philo->last_meal_time, ft_get_time());
	safe_increase_long(&philo->table->table_mutex, &philo->table->threads_running);
	assign_turns (philo);
	while (!simulation_finished(philo->table))
	{
		if (safe_get_bool(&philo->mutex, &philo->full))
			break ;
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
	return (NULL);
}
