/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:47:25 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/18 15:56:13 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads(t_table *table)
{
	while (!safe_get_bool(&table->mutex, &table->ready))
		;
}

bool	simulation_finished(t_table *table)
{
	return (safe_get_bool(&table->mutex, &table->end));
}

long	last_meal(t_philo *philo)
{
	long	ret;

	ft_safe_mutex (&philo->mutex, LOCK);
	ret = philo->last_meal_time;
	ft_safe_mutex (&philo->mutex, UNLOCK);
	return (ret);
}

long	full_philos_are(t_table *table)
{
	return (safe_get_long(&table->mutex, table->full_philos));
}
