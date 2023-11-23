/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:08:22 by aaronespino       #+#    #+#             */
/*   Updated: 2023/11/23 17:14:12 by aaespino         ###   ########.fr       */
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

void    parse_input(t_data *data, char **argv)
{
    data->philo_nbr = comprove_argv(argv[1]);
    data->time_to_die = comprove_argv(argv[2]) * 1000;
    data->time_to_eat = comprove_argv(argv[3]) * 1000;
    data->time_to_sleep = comprove_argv(argv[4]) * 1000;
    if (argv[5])
        data->limit_meals_nbr = comprove_argv(argv[5]);
    else
        data->limit_meals_nbr = -1;
}