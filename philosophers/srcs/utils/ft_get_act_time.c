/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_act_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:57:56 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/12 16:26:06 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

u_int64_t	ft_get_act_time(u_int64_t time)
{
	struct timeval	tv;
	u_int64_t		actual;

	if (gettimeofday(&tv, NULL))
		return(ft_error("gettimeofday() FAILURE\n"));
	actual = (tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000) - time;
	return (actual);
}
