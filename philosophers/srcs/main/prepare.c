/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:30:46 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/17 15:45:53 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//ASSIGN_FORKS
//Este programa sera usado por CALL_PHILOS
// NO LO COMPRENDO
//
static void	prepare_philos(t_table *table)
{
	
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
		philo->philo_id = i;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
		ft_safe_mutex(&philo->mutex, INIT);
		prepare_forks(philo, table->forks, i);
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
