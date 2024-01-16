/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/16 18:37:47 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)data;
	ft_usleep(table->time_to_die - (table->time_to_die / 4));
	while (i++ < table->philo_nbr && !(safe_get_bool(&table->mutex, &table->end))
		&& safe_get_long(&table->mutex, table->full_philos) == 0)
	{
		if (i == table->philo_nbr)
			i = 0;
		if (!(safe_get_bool(&table->philos[i].mutex, &table->philos[i].eating)))
		{
			ft_safe_mutex(&table->philos[i].mutex, LOCK);
			if ((ft_get_time() >= table->philos[i].time_to_die)
				&& table->philos[i].eating == false)
				philo_does(DIE, &table->philos[i]);
			ft_safe_mutex(&table->philos[i].mutex, UNLOCK);
		}
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
	{
		if ((ft_get_time() >= philo->time_to_die))
			philo_does(DIE, philo);
	}
	return (0);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_to_die = philo->time_to_die + ft_get_time();
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->table->time_to_eat / 10);
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		do_eat(philo);
		philo_does (THINK, philo);
		if (philo->meals_count == philo->table->limit_meals_nbr
			&& philo->table->limit_meals_nbr != -1)
			break ;
	}
	if (philo->meals_count == philo->table->limit_meals_nbr)
	{
		ft_safe_mutex(&philo->table->mutex, LOCK);
		philo->table->full_philos++;
		ft_safe_mutex(&philo->table->mutex, UNLOCK);
	}
	return ((void *)0);
}
