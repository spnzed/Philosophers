/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/12 19:21:18 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_action(t_philo *philo, char *str)
{
	philo->data->start_simulation = ft_get_time();
	if (philo->dead == false)
   		printf(BLUE"%ld ms \t" WHITE" %d %s\n"RESET, philo->data->start_simulation, philo->philo_id, str);
}

bool eat(t_philo *philo)
{
	if (philo->data->limit_meals_nbr)
		if (philo->meals_count >= philo->data->limit_meals_nbr)
			return (NULL);
	ft_safe_mutex(&philo->left->fork, LOCK);
	print_action(philo, YELLOW"has taken a fork");
	ft_safe_mutex(&philo->right->fork, LOCK);
	print_action(philo, YELLOW"has taken a fork");
	philo->meals_count++;
	philo_does (EAT, philo);
	philo->data->last_meal_time = ft_get_time();
	ft_safe_mutex(&philo->left->fork, UNLOCK);
	ft_safe_mutex(&philo->right->fork, UNLOCK);
	return (NULL);
}

void philo_does(t_philo_code code, t_philo *philo)
{
	printf(BLUE"HASTA AQUI 🥶\n"RESET);
	ft_safe_mutex(&philo->write_mutex, LOCK);
	if (EAT == code)
	{
		print_action(philo, YELLOW"is eating");
		ft_usleep((useconds_t) philo->data->time_to_eat);
	}
	if (SLEEP == code)
	{
		print_action(philo, CYAN"is sleeping");
		ft_usleep((useconds_t) philo->data->time_to_sleep);
	}
	if (THINK == code)
	{
		print_action(philo, WHITE"is thinking");
		ft_usleep((useconds_t) philo->data->time_to_eat);
	}
	else
		ft_error("Wrong code for philo_does: \n" GREEN"use <EAT> <SLEEP> <THINK>"RESET);
	ft_safe_mutex (&philo->write_mutex, UNLOCK);
}

static void assign_turns(t_philo *philo)
{
	philo = NULL;
	if (philo->philo_id % 2 == 0)
		philo_does(EAT, philo);
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	ft_safe_mutex(&philo->philo_mutex, LOCK);
	ft_safe_mutex(&philo->philo_mutex, UNLOCK);
	philo_does(THINK, philo);
	assign_turns (philo);
	while (!philo->dead)
	{
		philo_does(SLEEP, philo);
		philo_does(THINK, philo);
		if (philo->data->limit_meals_nbr > 0 
			&& philo->meals_count >= philo->data->limit_meals_nbr)
			philo->dead = true;
	}
	return (NULL);
}
