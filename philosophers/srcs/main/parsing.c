/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaronespinosa <aaronespinosa@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2023/11/13 23:04:18 by aaronespino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//  5       Number of tables
//  800     Time the table will die if doesnt eat
//  200     Time table takes to eat
//  200     Time table takes to sleep
//  7       Number of times tables eat

static long comprove_argv(char *str)
{
    long    num;

    num = ft_atol(str);
    if (num > INT_MAX)
        ft_error ("INT_MAX is the limit");
    return (num);
}

void    parse_input(t_table *table, char **argv)
{
    table->philo_nbr = (argv[1]);
    table->time_to_die = comprove_argv(argv[2]) * 1000;
    table->time_to_eat = comprove_argv(argv[3]) * 1000;
    table->time_to_sleep = comprove_argv(argv[4]) * 1000;
    if (argv[5])
        table->limit_meals_nbr = comprove_argv(argv[5]);
    else
        table->limit_meals_nbr = -1;
}