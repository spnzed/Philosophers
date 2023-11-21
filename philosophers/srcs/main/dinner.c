/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:18 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/21 19:00:23 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_eating(t_table *table, t_data *data)
{
	
}

/*
static void    *dinner_simulation(void *data)	//Dinner simu recibe cualquier data (void *data)
{
    t_philo        *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);				//haremos un boolean que devuelve si los threads son utilizables
    set_long(&philo->philo_mutex, &philo->last_meal_time, 
        gettime(MILLISECOND));					//ponemos el lastmealtime con gettime
    increase_long(&philo->table->table_mutex,
        &philo->table->threads_running_nbr);	//aumenta threads_running
    de_synchronize_philos(philo);				//repartir los turnos de comida, pares primero, impares piensan
    while (!simulation_finished(philo->table))	//mientras simulation no termina
    {
        if (get_bool(&philo->philo_mutex, &philo->full))//si get_bool devuelve que el philo esta lleno BREAK
            break ;
        eat(philo);								//comer
        precise_usleep(philo->table->time_to_sleep, philo->table);//sleep
        thinking(philo, false);					//pensar
    }
    return (NULL);
}
*/
