/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:31:03 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *data)
{
	t_philo	*philo;

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

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->table->start_simulation = ft_get_time();
	philo_does(THINK, philo);
	philo_does(FORK, philo);
	philo->time_to_die = philo->time_to_die + ft_get_time();
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
		ft_usleep(0);
	return (0);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_to_die = philo->time_to_die + ft_get_time();
	if (!(ft_safe_thread(&philo->supervisor, &supervisor,
				(void *)philo, CREATE)))
		return ((void *)1);
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		philo_does (THINK, philo);
		do_eat(philo);
	}
	if (!(ft_safe_thread(&philo->supervisor, NULL, NULL, JOIN)))
		return ((void *)1);
	return ((void *)0);
}
