/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaronespinosa <aaronespinosa@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/13 22:46:34 by aaronespino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



int	main (int argc , char **argv)
{
	t_table	table;
	t_philo	philo;

	if (argc == 5 || argc == 6)
	{
		parse_input(&philo, argv);
		prepare_table(&table);
		start_eating(&table);
		clean_dishes(&table);
	}
	else
		//error;
}