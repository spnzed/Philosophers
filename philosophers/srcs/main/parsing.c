/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2024/01/04 18:06:40 by aaespino         ###   ########.fr       */
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

void    parse_input(t_table *table, char **argv)
{
    table->philo_nbr = comprove_argv(argv[1]);
    table->time_to_die = comprove_argv(argv[2]);
    table->time_to_eat = comprove_argv(argv[3]);
    table->time_to_sleep = comprove_argv(argv[4]);
    table->threads_running = 0;
    table->start_simulation = 0;
    if (argv[5])
        table->limit_meals_nbr = comprove_argv(argv[5]);
    else
        table->limit_meals_nbr = -1;
}