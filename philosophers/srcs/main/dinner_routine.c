/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/19 20:57:16 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_turns(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
			ft_usleep(100);
	else if (philo->philo_id % 2)
		philo_does(THINK, philo);
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	safe_put_long(philo->philo_mutex, &philo->data->start_simulation, ft_get_time());
	safe_increase_long(philo->philo_mutex, &philo->data->threads_running);
	assign_turns (philo);
	while (!simulation_finished(philo->table))
	{
		eat(philo);
		philo_does(SLEEP, philo);
		philo_does(THINK, philo);
	}
	return (NULL);
}
