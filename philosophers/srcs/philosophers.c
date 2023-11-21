/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/21 18:31:13 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main (int argc , char **argv)
{
	t_table	table;
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, &data, argv);
		prepare_table(&table, &data);
		start_eating(&table, &data);
		clean_dishes(&table);
	}
	else
		ft_error("Input isn't the correct one.\n" 
			GREEN"Example: ./philosphers 5 800 800 500\n"RESET);
}