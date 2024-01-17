/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/17 17:28:30 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time_passed(long start)
{
	long	elapsed;

	elapsed = ft_get_time() - start;
	return (elapsed);
}

int	monitor_times_eaten(t_table *table)
{
	if (safe_get_long(&table->mutex, table->full_philos)
		 == table->philo_nbr)
	{
		safe_put_bool(&table->mutex, &table->end, true);
		return (1);
	}
	return (0);
}

// void	*monitor(void *data)
// {
// 	t_table	*table;
// 	int		i;

// 	i = 0;
// 	table = (t_table *)data;
// 	ft_usleep(table->time_to_die - (table->time_to_die / 4));
// 	while (i++ < table->philo_nbr && !(safe_get_bool(&table->mutex, &table->end))
// 		&& safe_get_long(&table->mutex, table->full_philos) == 0)
// 	{
// 		if (i == table->philo_nbr)
// 			i = 0;
// 		if (!(safe_get_bool(&table->philos[i].mutex, &table->philos[i].eating)))
// 		{
// 			ft_safe_mutex(&table->philos[i].mutex, LOCK);
// 			if ((ft_get_time() >= table->philos[i].time_to_die)
// 				&& table->philos[i].eating == false)
// 				philo_does(DIE, &table->philos[i]);
// 			ft_safe_mutex(&table->philos[i].mutex, UNLOCK);
// 		}
// 	}
// 	return (NULL);
// }

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)data;
	while (i++ < table->philo_nbr && !(safe_get_bool(&table->mutex, &table->end))
		&& safe_get_long(&table->mutex, table->full_philos) == 0)
	{
		if (safe_get_long(&table->philos[i].mutex, table->philos[i].last_meal_time)
		&& safe_get_long(&table->philos[i].mutex, table->philos[i].last_meal_time) > 0)
		{
			if (ft_time_passed(safe_get_long(&table->philos[i].mutex, table->philos[i].last_meal_time)) >= table->time_to_die)
			{
				philo_does(DIE, &table->philos[i]);
				break ;
			}
		}
		if (table->limit_meals_nbr > 0 && monitor_times_eaten(table) == 1)
			break ;
		i++;
		if (i == table->philo_nbr)
			i = 0;
		usleep (100);
	}
	return (NULL);
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

static void	wait_all_threads(t_table *table)
{
	while (!safe_get_bool(&table->mutex, &table->ready))
		;
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	safe_put_long(&philo->mutex, &philo->last_meal_time, ft_get_time());
	//philo->time_to_die = philo->time_to_die + ft_get_time();
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->table->time_to_eat / 10);
	while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
		if (philo->meals_count == philo->table->limit_meals_nbr
			&& philo->table->limit_meals_nbr != -1)
			break ;
		do_eat(philo);
		philo_does (THINK, philo);
	}
	if (philo->meals_count == philo->table->limit_meals_nbr)
	{
		ft_safe_mutex(&philo->table->mutex, LOCK);
		philo->table->full_philos++;
		ft_safe_mutex(&philo->table->mutex, UNLOCK);
	}
	return ((void *)0);
}
