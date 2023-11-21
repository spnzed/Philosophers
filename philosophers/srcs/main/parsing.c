/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2023/11/21 17:00:05 by aaespino         ###   ########.fr       */
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
        ft_error ("INT MAX is the limit sweetie");
    else if (ft_atol(arg) < INT_MIN)
        ft_error ("INT MAX is the limit sweetie");
    else
        return (ft_atoi(arg));
        
}

void    parse_input(t_data *data, t_table *table, char **argv)
{
    data->philo_nbr = comprove_argv(argv[0]);
    data->time_to_die = comprove_argv(argv[1]) * 1000;
    data->time_to_eat = comprove_argv(argv[2]) * 1000;
    data->time_to_sleep = comprove_argv(argv[3]) * 1000;
    if (argv[4])
        data->limit_meals_nbr = comprove_argv(argv[4]);
    else
        data->limit_meals_nbr = -1;
}