/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaronespinosa <aaronespinosa@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:27 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/13 23:05:43 by aaronespino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    prepare_table(t_table *table)
{
    int i;

    i = 0;
    table->end_simulation = false;
    table->threads_ready = false;
    table->threads_running = 0;
    table->philos = ft_safe_malloc(table->philo_nbr * sizeof(t_philo));
    table->forks = ft_safe_malloc(table->philo_nbr * sizeof(t_fork));
}