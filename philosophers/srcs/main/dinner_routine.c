/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:50:12 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/13 17:13:36 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_action(t_philo *philo, char *str)
{
	ft_safe_mutex(philo->write_mutex, LOCK);
	uint64_t	time;
	
	time = ft_get_time();
	time -= philo->data->start_simulation;
	if (philo->dead == false)
   		printf(BLUE"[%06llu ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, str);
	ft_safe_mutex (philo->write_mutex, UNLOCK);
}

bool eat(t_philo *philo)
{
	ft_safe_mutex(&philo->left->fork, LOCK);
	print_action(philo, YELLOW"has taken a fork");
	ft_safe_mutex(&philo->right->fork, LOCK);
	print_action(philo, YELLOW"has taken a fork");
	philo_does(EAT, philo);
	printf(RED"HASTA AQUI 🥶\n"RESET);
	if (philo->data->limit_meals_nbr)
		if (philo->meals_count >= philo->data->limit_meals_nbr)
			return (NULL);
	philo->meals_count++;
	philo_does (EAT, philo);
	philo->data->last_meal_time = ft_get_time();
	ft_safe_mutex(&philo->left->fork, UNLOCK);
	ft_safe_mutex(&philo->right->fork, UNLOCK);
	return (NULL);
}

void philo_does(t_philo_code code, t_philo *philo)
{
	if (EAT == code)
	{
		print_action(philo, YELLOW"is eating\t😋"RESET);
		ft_usleep(philo->data->time_to_eat);
	}
	else if (SLEEP == code)
	{
		print_action(philo, CYAN"is sleeping\t😴"RESET);
		ft_usleep(philo->data->time_to_sleep);
	}
	else if (THINK == code)
	{
		print_action(philo, WHITE"is thinking\t🤔"RESET);
		ft_usleep(philo->data->time_to_eat);
	}
	else
		ft_error("Wrong code for philo_does: \n" GREEN"use <EAT> <SLEEP> <THINK>"RESET);
}

static void assign_turns(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		if (!eat(philo))
			return ;
}

void	*dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	ft_safe_mutex(philo->philo_mutex, LOCK);
	ft_safe_mutex(philo->philo_mutex, UNLOCK);
	philo->data->start_simulation = ft_get_time();
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
