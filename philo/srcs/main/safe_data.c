/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:38:01 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:14:22 by aaespino         ###   ########.fr       */
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
	ft_safe_mutex (mutex, LOCK);
	*dest = val;
	ft_safe_mutex (mutex, UNLOCK);
}

bool	safe_get_bool(t_mutex *mutex, bool *val)
{
	bool	ret;

	ft_safe_mutex (mutex, LOCK);
	ret = *val;
	ft_safe_mutex (mutex, UNLOCK);
	return (ret);
}
