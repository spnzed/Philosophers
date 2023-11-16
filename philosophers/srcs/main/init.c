/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:27 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/16 18:54:22 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//ASSIGN_FORKS
//Este programa sera usado por CALL_PHILOS
// NO LO COMPRENDO
/* 1

*/

/* 2

*/

//CALL_PHILOS
/* 1
Añadir un puntero de nuestra estructura de filos
*/

/* 2
Recorremos de la misma forma que "prepare table"
    Inicializamos todos los datos de philos
*/


void    prepare_table(t_table *table)
{
    int i;

    i = 0;
    table->end_simulation = false;
    table->threads_ready = false;
    table->threads_running = 0;
    //table->philos = ft_safe_malloc(table->philo_nbr * sizeof(t_philo));
    //table->forks = ft_safe_malloc(table->philo_nbr * sizeof(t_fork));
    while (i < table->philo_nbr)
    {
        ft_safe_mutex (&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
    }
    //philoinit
}