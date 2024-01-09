/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/09 19:22:37 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	philo->table->start_simulation = ft_get_time();
	do_think(philo);
	philo_does(DIE, philo);
	return ((void *) 0);
}

void	*monitor(void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;
	printf("KELOKEEE\n");
	philo_does(DIE, philo);
	while (!philo->table->end)
	{
		ft_safe_mutex(&philo->mutex, LOCK);
		if (philo->table->full_philos >= philo->table->philo_nbr)
			philo->table->end = 1;
		ft_safe_mutex(&philo->mutex, UNLOCK);
	}
	return (NULL);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!(philo->table->dead))
	{
		ft_safe_mutex(&philo->mutex, LOCK);
		if (ft_get_time() >= philo->time_to_die && !philo->eating)
			philo_does(DIE, philo);
		if (philo->meals_count == philo->limit_meals_nbr)
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
	if (!(ft_safe_thread(&philo->supervisor, &supervisor, &philo->supervisor, CREATE)))
		return ((void *)1);
	while (!(philo->table->dead))
	{
		do_eat(philo);
		philo_does (THINK, philo);
	}
	if (!(ft_safe_thread(&philo->supervisor, &supervisor, &philo->supervisor, JOIN)))
		return ((void *)1);
	return ((void *)0);
}
