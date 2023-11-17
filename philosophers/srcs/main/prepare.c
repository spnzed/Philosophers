/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/17 16:39:45 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	distribute_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;
	int philo_position;

	philo_nbr = (int)philo->table->philo_nbr;
	philo_pos = i;
	if (philo->id % 2 != 0)
	{
		philo->left = &forks[(philo_pos + 1) % philo_nbr];
		philo->right = &forks[philo_pos];
	}
	else
	{
		philo->left = &forks[philo_pos];
		philo->right = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	prepare_philos(t_table *table)
{
	int		i;
	int		ph_nbr;
	t_philo	*philo;

	i = 0;
	philo_nbr = (int)table->philo_nbr;
	while (i < philo_nbr)
	{
		philo = table_philos[i];
		philo->philo_id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
		ft_safe_mutex(&philo->mutex, INIT);
		distribute_forks(philo, table->forks, i);
	}
}

void    prepare_table(t_table *table)
{
    int i;

    i = 0;
    table->end_simulation = false;
    table->threads_ready = false;
    table->threads_running = 0;
    table->philos = ft_safe_malloc(table->philo_nbr * sizeof(t_philo));
    table->forks = ft_safe_malloc(table->philo_nbr * sizeof(t_fork));
    while (i < table->philo_nbr)
    {
        ft_safe_mutex (&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
    }
    prepare_philosophers(table);
}
