/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/23 18:42:12 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_state(t_mutex *mutex, bool *val)
{
	bool ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

static void	wait_threads(t_table *table)
{
	while (!check_state(&table->table_mutex, &table->threads_ready))
		;
}

static void	set_last_meal(t_mutex *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

static void increase_meals(t_mutex *mutex, long *count)
{
	pthread_mutex_lock(mutex);
	count++;
	pthread_mutex_unlock(mutex);
}

static void assign_turns(t_philo *philo)
{
	philo = NULL;
	// if (philo->philo_id % 2 == 0)
	// 	eating(philo);
	// else
	// 	thinking(philo);
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	printf("HHHHHHHHHHHH\n");
	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_last_meal(&philo->philo_mutex, &philo->data->last_meal_time, ft_get_time());
	increase_meals(&philo->philo_mutex, &philo->data->threads_running);
	assign_turns (philo);
	//mientras simulation no termina
		//si get_bool devuelve que el philo esta lleno BREAK
		//comer
		//sleep
		//pensar
	return (NULL);
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
