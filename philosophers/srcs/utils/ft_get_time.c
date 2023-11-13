/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:57:56 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/13 19:10:31 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

u_int64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return(ft_error("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
