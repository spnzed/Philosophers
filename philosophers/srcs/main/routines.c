/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/22 19:47:23 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo()
{   
	
}

void	monitor()
{    
	
}

bool	check_state(t_mutex *mutex, bool *val)
{
	bool ret;

	if (pthread_mutex_lock(mutex) == 0)
		return (NULL);
	ret = *val;
	if (pthread_mutex_unlock(mutex) == 0)
		return (NULL);
	return (ret);
}

void	wait_threads(t_table *table)
{
	while (!check_state(&table->table_mutex, table->threads_ready))
		;
}

void	*dinner_routine(t_philo *philo)
{ 
	wait_threads(philo->table);
	//ponemos el lastmealtime con gettime
	//aumenta threads_running
	//repartir los turnos de comida, pares primero, impares piensan
	//mientras simulation no termina
		//si get_bool devuelve que el philo esta lleno BREAK
		//comer
		//sleep
		//pensar
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
