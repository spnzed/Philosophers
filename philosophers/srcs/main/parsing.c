/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2023/12/22 19:27:16 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//  5       Number of philos
//  800     Time the table will die if doesnt eat
//  200     Time table takes to eat
//  200     Time table takes to sleep
//  7       Number of times tables eat

static int comprove_argv(char *arg)
{
    if (ft_atol(arg) > INT_MAX)
        return (ft_error ("INT MAX is the limit sweetie"));
    return (ft_atoi(arg));
}

void	assign_table_data(t_philo *philo, t_data *data)
{
	philo->data->philo_nbr = data->philo_nbr;
	philo->data->time_to_die = data->time_to_die;
	philo->data->time_to_eat = data->time_to_eat;
	philo->data->time_to_sleep = data->time_to_sleep;
	philo->data->limit_meals_nbr = data->limit_meals_nbr;
	philo->data->threads_running = 0;
	philo->data->start_simulation = 0;
	philo->data->last_meal_time = 0;
}

bool	init_mutex(t_table *table, t_data *data)
{
	int i;

	i = 0;
	if (!(ft_safe_mutex(&table->table_mutex, INIT)))
    	return (NULL);	
	if (!(ft_safe_mutex(&table->write_mutex, INIT)))
    	return (NULL);
	while (i < data->philo_nbr)
	{
		if (!(ft_safe_mutex(&table->forks[i].fork, INIT)))
        	return (NULL);
		i++;
	}
	return (true);
}

bool	init_malloc(t_table *table, t_data *data)
{
	table->philos = malloc(data->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (NULL);
	table->forks = malloc(data->philo_nbr * sizeof(t_fork));
	if (!table->forks)
		return (NULL);
	return (true);
}

void    parse_input(t_data *data, char **argv)
{
    data->philo_nbr = comprove_argv(argv[1]);
    data->time_to_die = comprove_argv(argv[2]);
    data->time_to_eat = comprove_argv(argv[3]);
    data->time_to_sleep = comprove_argv(argv[4]);
    data->threads_running = 0;
    data->start_simulation = 0;
    data->last_meal_time = 0;
    if (argv[5])
        data->limit_meals_nbr = comprove_argv(argv[5]);
    else
        data->limit_meals_nbr = -1;
}