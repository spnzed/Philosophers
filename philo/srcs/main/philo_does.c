/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:55 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/18 14:23:04 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_act(long time, int id, char *string)
{
	printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, id, string);
}

static void	print_well(t_philo_code code, long time, int id)
{
	if (id > 99)
	{
		if (SLEEP == code)
			print_act(time, id, CYAN"is sleeping\t [😴]");
		if (THINK == code)
			print_act(time, id, WHITE"is thinking\t [🤔]");
	}
	else
	{
		if (SLEEP == code)
			print_act(time, id, CYAN"is sleeping\t\t [😴]");
		if (THINK == code)
			print_act(time, id, WHITE"is thinking\t\t [🤔]");
	}
}

void	philo_does(t_philo_code code, t_philo *philo)
{
	long	time;

	ft_safe_mutex(&philo->table->write, LOCK);
	time = ft_get_time() - philo->table->start_simulation;
	if ((DIE == code) && !simulation_finished(philo->table))
	{
		print_act(time, philo->philo_id, RED"has died \t\t [💀]");
		safe_put_bool(&philo->table->mutex, &philo->table->end, true);
		ft_usleep(300);
	}
	if (!simulation_finished(philo->table))
	{
		if (FORK == code)
			print_act(time, philo->philo_id, YELLOW"has taken a fork \t [🍴]");
		if (EAT == code)
			print_act(time, philo->philo_id, GREEN"is eating\t\t [😋]");
		if (SLEEP == code)
			print_well(SLEEP, time, philo->philo_id);
		if (THINK == code)
			print_well(THINK, time, philo->philo_id);
	}
	ft_safe_mutex (&philo->table->write, UNLOCK);
}
