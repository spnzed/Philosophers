/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:18 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/22 19:55:25 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	call_philosophers(t_table *table, t_data *data)
{
	int i;

    i = 0;
    if (!data->limit_meals_nbr)
        return ;
    else if (data->limit_meals_nbr == 1)
    {
        if (pthread_create(table->philos[0].thread_id, NULL, one_philo, 
            &table->philos[0]) == 0)
            return (1);
    }
    else
    {
        while (i < data->philo_nbr)
        {
            if (pthread_create(table->philos[i].thread_id, NULL, 
                    dinner_routine, &table->philos[i]) == 0)
                return (1);
            i++;
        }
    }
    if (pthread_create(table->monitor, NULL, monitor, table) == 0);
        return (1);
    data->start_simulation = ft_get_time();
}

static void handle_threads(t_table *table, t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nbr)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
}

void    start_eating (t_table *table, t_data *data)
{
    call_philosophers(table, data);
    //lock->mutex and ✅ bool "threadsready"
    close_threads(table, data);
    //(UN)?lock->mutex and ✅ bool "endsimu"
    pthread_join(table->monitor, NULL);
}
