/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/20 17:47:29 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_turns(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
			ft_usleep(50);
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
	while (simulation_finished(philo->table) == false)
	{
		if (simulation_finished(philo->table) == true)
			return (NULL);
		eat(philo);
		if (simulation_finished(philo->table) == true)
			return (NULL);
		philo_does(SLEEP, philo);
		if (simulation_finished(philo->table) == true)
			return (NULL);
		philo_does(THINK, philo);
		if (simulation_finished(philo->table) == true)
			return (NULL);
	}
	return (NULL);
}
