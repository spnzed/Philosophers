/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:38:01 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/16 18:02:50 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_increase_long(t_mutex *mutex, long *count)
{
	ft_safe_mutex (mutex, LOCK);
	(*count)++;
	ft_safe_mutex (mutex, UNLOCK);
}

void	safe_put_long(t_mutex *mutex, long *dest, long val)
{
	ft_safe_mutex (mutex, LOCK);
	*dest = val;
	ft_safe_mutex (mutex, UNLOCK);
}

long	safe_get_long(t_mutex *mutex, long val)
{
	long	ret;

	ft_safe_mutex (mutex, LOCK);
	ret = val;
	ft_safe_mutex (mutex, UNLOCK);
	return (ret);
}

void	safe_put_bool(t_mutex *mutex, bool *dest, bool val)
{
	// printf("val:::::%i|\n", val);
	ft_safe_mutex (mutex, LOCK);
	*dest = val;
	ft_safe_mutex (mutex, UNLOCK);
}

bool	safe_get_bool(t_mutex *mutex, bool *val)
{
	bool	ret = true;

	// printf("fasfasf::%i|\n", ret);
	ft_safe_mutex (mutex, LOCK);
	ret = *val;
	ft_safe_mutex (mutex, UNLOCK);
	// printf("fasfasf::%i|\n", ret);
	return (ret);
}
