/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:57:56 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/12 16:42:22 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}
