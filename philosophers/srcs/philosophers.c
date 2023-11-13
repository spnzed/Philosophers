/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:28 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/13 17:04:26 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main (int argc , char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		prepare_table(&table);
		start_eating(&table);
		clean_dishes(&table);
	}
	else
		//error;
}