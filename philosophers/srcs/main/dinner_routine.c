/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/14 20:05:49 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_turns(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			ft_usleep(500);
	}
	else
	{
		if (philo->philo_id % 2)
			philo_does(THINK, philo);
	}
}

void	*dinner_routine(void *data)
{
	bool	full;
	t_philo *philo;

	full = 0;
	philo = (t_philo *)data;
	ft_safe_mutex(philo->philo_mutex, LOCK);
	ft_safe_mutex(philo->philo_mutex, UNLOCK);
	safe_put_long(philo->philo_mutex, &philo->data->start_simulation, ft_get_time());
	safe_increase_long(&philo->table->table_mutex, &philo->table->table_data->threads_running);
	assign_turns (philo);
	while (!full)
	{
		if (!eat(philo))
			return(NULL);
		philo_does(SLEEP, philo);
		philo_does(THINK, philo);
		if (philo->data->limit_meals_nbr 
			&& philo->meals_count >= philo->data->limit_meals_nbr)
			safe_put_bool(philo->philo_mutex, &philo->full, true);
		full = safe_get_bool(philo->philo_mutex, &philo->full);
	}
	return (NULL);
}
