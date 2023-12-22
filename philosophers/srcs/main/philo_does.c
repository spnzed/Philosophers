/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:55 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/20 17:47:53 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_action(t_philo *philo, char *str)
{
	uint64_t	time;
	uint64_t	minus;
	uint64_t	time_to_die;

	ft_safe_mutex(philo->write_mutex, LOCK);
	time = ft_get_time();
	minus = safe_get_long(philo->philo_mutex, philo->data->start_simulation);
	time_to_die = safe_get_long(philo->philo_mutex, philo->data->time_to_die);
	time -= minus;
// 	printf(BLUE"[%06llu ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, str);
 	printf("%012llu %d %s\n", time, philo->philo_id, str);
	ft_safe_mutex (philo->write_mutex, UNLOCK);
}

bool	dead(t_philo *philo)
{
	bool	dead;

	dead = safe_get_bool(philo->philo_mutex, &philo->dead);
	safe_put_bool(philo->philo_mutex, &philo->dead, true);
	philo_does (DIE, philo);
	return (NULL);
}

bool eat(t_philo *philo)
{
	ft_safe_mutex(&philo->left->fork, LOCK);
	print_action(philo, "has taken a fork");
//	print_action(philo, YELLOW"has taken a fork \t [🍴]");
	ft_safe_mutex(&philo->right->fork, LOCK);
	print_action(philo, "has taken a fork");
//	print_action(philo, YELLOW"has taken a fork \t [🍴]");
	safe_put_long(&philo->table->table_mutex, &philo->data->last_meal_time, ft_get_time());
	philo->meals_count++;
	philo_does(EAT, philo);
	if (philo->data->limit_meals_nbr 
		&& philo->meals_count >= philo->data->limit_meals_nbr)
		safe_put_bool(philo->philo_mutex, &philo->full, true);
	ft_safe_mutex(&philo->left->fork, UNLOCK);
	ft_safe_mutex(&philo->right->fork, UNLOCK);
	return (0);
}

void philo_does(t_philo_code code, t_philo *philo)
{
	// if (safe_get_bool(philo->philo_mutex, &philo->full))
	// 	return ;
	if (EAT == code)
	{
		print_action(philo, "is eating"RESET);
//		print_action(philo, GREEN"is eating\t\t [😋]"RESET);
		ft_usleep(philo->data->time_to_eat);
	}
	if (SLEEP == code)
		{
		print_action(philo, "is sleeping"RESET);
//		print_action(philo, CYAN"is sleeping\t\t [😴]"RESET);
		ft_usleep(philo->data->time_to_sleep);
	}
	if (THINK == code)
	{
		print_action(philo, "is thinking"RESET);
//		print_action(philo, WHITE"is thinking\t\t [🤔]"RESET);
			if (philo->table->philo_nbr % 2 == 0)
			return ;
		ft_usleep(((philo->data->time_to_eat * 2) - philo->data->time_to_sleep));
	}
	if (DIE == code)
		print_action(philo, "has died");
//		print_action(philo, RED"has died \t\t [💀]");
}
