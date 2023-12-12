/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/12 14:57:37 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	clean_dishes(t_table *table)
{
	table = NULL;
	return(NULL);
}

int	main (int argc , char **argv)
{
	t_table	table;
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		if (!(prepare_table(&table, &data)))
		{
			clean_dishes(&table);
			return(ft_error("Table can't be prepared.\n"));
		}
		else if (!(start_dinning(&table, &data)))
		{
			clean_dishes(&table);
			return(ft_error("Dinner interrupted.\n"));
		}
	}
	else
		return (ft_error("Input isn't the correct one.\n" 
			GREEN"Example: ./philosphers 5 800 800 500\n"RESET));
}
