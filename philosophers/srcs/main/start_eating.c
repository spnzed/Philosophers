/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:18 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/23 18:35:55 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	call_philosophers(t_table *table, t_data *data)
{
	long i;

    i = 0;
    if (!data->limit_meals_nbr)
        return (NULL);
    else if (data->limit_meals_nbr == 1)
    {
        if (!(ft_safe_thread(table->philos[0].thread_id, one_philo, 
                &table->philos[0], CREATE)))
            return (NULL);
    }
    else
    {
        while (i < data->philo_nbr)
        {
            if (!(ft_safe_thread(table->philos[i].thread_id, dinner_routine, 
                &table->philos[i], CREATE)))
                return (NULL);
            i++;
        }
    }
    if (!(ft_safe_thread(&table->monitor, monitor, 
               &table, CREATE)))
        return (NULL);
    data->start_simulation = ft_get_time();
    return (true);
}

static void handle_threads(t_table *table, t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nbr)
    {
        pthread_join(*table->philos[i].thread_id, NULL);
        i++;
    }
}

bool    start_eating (t_table *table, t_data *data)
{
    if (!(call_philosophers(table, data)))
        return (NULL);
    //lock->mutex and ✅ bool "threadsready"
    handle_threads(table, data);
    //(UN)?lock->mutex and ✅ bool "endsimu"
    pthread_join(table->monitor, NULL);
    return (true);
}