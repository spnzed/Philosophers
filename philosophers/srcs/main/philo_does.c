/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:55 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/05 17:42:38 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	do_eat(t_philo *philo)
{
	ft_safe_mutex(&philo->left->fork, LOCK);
	philo_does(FORK, philo);
	ft_safe_mutex(&philo->right->fork, LOCK);
	philo_does(FORK, philo);
	safe_put_long(&philo->mutex, &philo->last_meal_time, ft_get_time());
	philo->meals_count++;
	philo_does(EAT, philo);
	ft_usleep(philo->table->time_to_die);
	if (philo->table->limit_meals_nbr > 0
		&& philo->meals_count == philo->table->limit_meals_nbr)
		safe_put_bool(&philo->mutex, &philo->full, true);
	ft_safe_mutex(&philo->left->fork, UNLOCK);
	ft_safe_mutex(&philo->right->fork, UNLOCK);
	return (0);
}

bool	do_sleep(t_philo *philo)
{
	philo_does (SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep);
	return (NULL);
}

bool	do_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	philo_does(THINK, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return (NULL);
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think);
	return (0);
}

void philo_does(t_philo_code code, t_philo *philo)
{
	long		time;

	time = ft_get_time() - philo->table->start_simulation;
	if (safe_get_bool(&philo->mutex, &philo->full))
		return ;
	ft_safe_mutex(&philo->table->write_mutex, LOCK);
	if (FORK == code && !simulation_finished(philo->table))
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, YELLOW"has taken a fork \t [🍴]");
	else if (EAT == code && !simulation_finished(philo->table))
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, GREEN"is eating\t\t [😋]");
	else if (SLEEP == code && !simulation_finished(philo->table))
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, CYAN"is sleeping\t\t [😴]");
	else if (THINK == code && !simulation_finished(philo->table))
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, WHITE"is thinking\t\t [🤔]");
	else if (DIE == code && !simulation_finished(philo->table))
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, RED"has died \t\t [💀]");
	ft_safe_mutex (&philo->table->write_mutex, UNLOCK);
}