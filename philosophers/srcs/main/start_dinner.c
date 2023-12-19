/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:18 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/19 20:03:51 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void handle_threads(t_table *table, t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        ft_safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
}

static bool	call_philosophers(t_table *table, t_data *data)
{
	long i;

    i = 0;
    if (!data->limit_meals_nbr)
        return (NULL);
    else if (data->philo_nbr == 1)
    {
        if (!(ft_safe_thread(&table->philos[0].thread_id, one_philo, 
                &table->philos[0], CREATE)))
            return (NULL);
    }
    else
    {
        while (i < data->philo_nbr)
        {
            if (!(ft_safe_thread(&table->philos[i].thread_id, dinner_routine, 
                &table->philos[i], CREATE)))
                return (NULL);
            i++;
        }
    }
    if (!(ft_safe_thread(&table->monitor, monitor, 
               table, CREATE)))
        return (NULL);
    data->start_simulation = ft_get_time();
    handle_threads (table, data);
    ft_safe_thread(&table->monitor, NULL, NULL, JOIN);
    return(true);
}

bool    start_dinning (t_table *table, t_data *data)
{
    //bool done;

    if (!(call_philosophers(table, data)))
        return (NULL);
	//printf(MAGENTA"HASTA AQUI\n"RESET);
    //done = safe_get_bool(&table->table_mutex, &table->end_simu);
    // if (done)
    // {
    //     clean_dishes (table);
    //     return (true);
    // }
    // else
    //     return (NULL);
    return (true);
}