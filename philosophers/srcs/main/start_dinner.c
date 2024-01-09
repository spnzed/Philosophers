/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:18 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/09 18:42:57 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void handle_threads(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
        ft_safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
}

bool	 simulation_finished(t_table *table)
{
	return (safe_get_bool(&table->mutex, &table->end));
}

bool philo_is_full(t_philo *philo)
{
	return (safe_get_bool(&philo->mutex, &philo->full));
}

int start_dinning(t_table *table)
{
	long i;

    i = 0;
	table->start_simulation = ft_get_time();
    if (table->limit_meals_nbr > 0)
    {
        if (!(ft_safe_thread(&table->monitor, monitor, 
                table, CREATE)))
            return (ft_error("Error while creating threads\n"));
    }
    if (table->philo_nbr == 1)
    {
        if (!(ft_safe_thread(&table->philos[0].thread_id, one_philo, 
            &table->philos[0], CREATE)))
            return (1);
    }
    else
    {
        while (i < table->philo_nbr)
        {
            if (!(ft_safe_thread(&table->philos[i].thread_id, &dinner_routine, 
                &table->philos[i], CREATE)))
                return (ft_error("Error while creating threads\n"));
            i++;
            ft_usleep(1);
        }
    }
    handle_threads(table);
    return (0);
}
