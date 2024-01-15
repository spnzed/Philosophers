/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:46:55 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 15:08:28 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	ft_safe_mutex(&philo->left->fork, LOCK);
	philo_does(FORK, philo);
	ft_safe_mutex(&philo->right->fork, LOCK);
	philo_does(FORK, philo);
}

static void	drop_forks(t_philo *philo)
{
	ft_safe_mutex(&philo->left->fork, UNLOCK);
	ft_safe_mutex(&philo->right->fork, UNLOCK);
	philo_does(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep);
}

void	do_eat(t_philo *philo)
{
	if (philo->table->limit_meals_nbr > 0)
	{
		if (philo->meals_count >= philo->table->limit_meals_nbr)
			while (!(safe_get_bool(&philo->table->mutex, &philo->table->end)))
				ft_usleep(100);
	}
	take_forks(philo);
	ft_safe_mutex(&philo->mutex, LOCK);
	philo->eating = true;
	philo->time_to_die = ft_get_time() + philo->table->time_to_die;
	philo_does(EAT, philo);
	philo->meals_count++;
	ft_usleep(philo->table->time_to_eat);
	philo->eating = false;
	ft_safe_mutex(&philo->mutex, UNLOCK);
	drop_forks(philo);
}

void	do_sleep(t_philo *philo)
{
	philo_does (SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep);
}

void	do_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	philo_does(THINK, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42);
}

void philo_does(t_philo_code code, t_philo *philo)
{
	long		time;

	ft_safe_mutex(&philo->table->write, LOCK);
	time = ft_get_time() - philo->table->start_simulation;
	if ((DIE == code) && !(safe_get_bool(&philo->table->mutex, &philo->table->end)))
	{
 		printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, RED"has died \t\t [💀]");
		safe_put_bool(&philo->table->mutex, &philo->table->end, true);
	}
	if (!safe_get_bool(&philo->table->mutex, &philo->table->end))
	{
		if (FORK == code)
			printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, YELLOW"has taken a fork \t [🍴]");
		if (EAT == code)
			printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, GREEN"is eating\t\t [😋]");
		if (SLEEP == code)
			printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, CYAN"is sleeping\t\t [😴]");
		if (THINK == code)
			printf(BLUE"[%06ld ms] \t" WHITE" %d %s\n"RESET, time, philo->philo_id, WHITE"is thinking\t\t [🤔]");		
	}
	ft_safe_mutex (&philo->table->write, UNLOCK);
}