/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:55 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:43:53 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_act(long time, int id, char *string)
{
	printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, id, string);
}

void	philo_does(t_philo_code code, t_philo *philo)
{
	long	time;

	ft_safe_mutex(&philo->table->write, LOCK);
	time = ft_get_time() - philo->table->start_simulation;
	if ((DIE == code) && !(safe_get_bool(&philo->table->mutex,
				&philo->table->end)))
	{
		print_act(time, philo->philo_id, RED"has died \t\t [💀]");
		safe_put_bool(&philo->table->mutex, &philo->table->end, true);
	}
	if (!safe_get_bool(&philo->table->mutex, &philo->table->end))
	{
		if (FORK == code)
			print_act(time, philo->philo_id, YELLOW"has taken a fork \t [🍴]");
		if (EAT == code)
			print_act(time, philo->philo_id, GREEN"is eating\t\t [😋]");
		if (SLEEP == code)
			print_act(time, philo->philo_id, CYAN"is sleeping\t\t [😴]");
		if (THINK == code)
			print_act(time, philo->philo_id, WHITE"is thinking\t\t [🤔]");
	}
	ft_safe_mutex (&philo->table->write, UNLOCK);
}
