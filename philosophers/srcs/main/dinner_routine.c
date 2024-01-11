/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/11 19:41:28 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->table->full_philos >= philo->table->philo_nbr)
			philo->table->end = true;
		pthread_mutex_unlock(&philo->table->mutex);
	}
	return (NULL);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		ft_safe_mutex(&philo->mutex, LOCK);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
			philo_does(DIE, philo);
		if (philo->meals_count == philo->table->limit_meals_nbr)
		{
			ft_safe_mutex(&philo->table->mutex, LOCK);
			philo->table->full_philos++;
			philo->meals_count++;
			ft_safe_mutex(&philo->table->mutex, UNLOCK);
		}
		ft_safe_mutex(&philo->mutex, UNLOCK);
	}
	return (0);
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	philo->time_to_die = philo->time_to_die + ft_get_time();
	if (!(ft_safe_thread(&philo->supervisor, &supervisor, (void *)philo, CREATE)))
		return ((void *)1);
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		philo_does (THINK, philo);
		do_eat(philo);
	}
	if (!(ft_safe_thread(&philo->supervisor, &supervisor, NULL, JOIN)))
		return ((void *)1);
	return ((void *)0);
}

int	one_philo(t_table *table)
{
	table->start_simulation = ft_get_time();
	if (!(ft_safe_thread(&table->philos[0].thread_id, &dinner_routine, &table->philos[0], CREATE)))
		return (ft_error("Error while creating thread"));
	ft_safe_thread(&table->philos[0].thread_id, NULL, NULL, JOIN);
	while (!table->end)
		ft_usleep(0);
	clean_dishes(table);
	return (0);
}

int start_dinning(t_table *table)
{
	int 		i;
	pthread_t	t_monitor;

    i = 0;
	table->start_simulation = ft_get_time();
    if (table->limit_meals_nbr > 0)
    {
        if (!(ft_safe_thread(&t_monitor, &monitor, &table->philos[0], CREATE)))
            return (ft_error("Error while creating monitor\n"));
    }
    while (i < table->philo_nbr)
    {
        if (!(ft_safe_thread(&table->threads[i], &dinner_routine, &table->philos[i], CREATE)))
            return (ft_error("Error while creating threads\n"));
        i++;
        ft_usleep(1);
	}
    i = -1;
    while (++i < table->philo_nbr)
        ft_safe_thread(&table->threads[i], NULL, NULL, JOIN);
	if (table->limit_meals_nbr > 0)
    	ft_safe_thread(&t_monitor, NULL, NULL, JOIN);
    return (0);
}
