/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:57:56 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/13 16:36:35 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

u_int64_t	ft_get_time(void)
{
	u_int64_t		now;
	struct timeval	va;

	gettimeofday(&va, NULL);
	now = va.tv_sec * 1000;
	now += va.tv_usec / 1000;
	return (now);
}
