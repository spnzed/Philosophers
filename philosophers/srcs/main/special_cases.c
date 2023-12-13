/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:28:24 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/13 19:27:35 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *pointer)
{
	pointer = NULL;
	return (pointer);
}

void	*monitor(t_table *table)
{
	int		i;
	long 	nbr;
	long 	time;

	nbr = table->philos->data->philo_nbr;
	while (!table->philos->dead)
	{
		i = 0;
		while (i < nbr)
		{
			time = table->philos->data->last_meal_time;
			if (time > table->philos->data->time_to_die)
			{
				dead(&table->philos[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

// void	*death_check(t_table *table)
// {
// 	int			i;
// 	int			n;
// 	long long	time;

// 	n = table->data.philo_amount;
// 	while (1 && !table->data.dead)
// 	{
// 		i = 0;
// 		while (i < n)
// 		{
// 			time = get_time_ms(table->philos[i].last_meal);
// 			if (time > table->philos[i].data->time_to_die)
// 			{
// 				philo_dead(&table->philos[i]);
// 				return (NULL);
// 			}
// 		}
// 		usleep_wrapper(100, table->data.dead);
// 	}
// 	return (NULL);
// }
