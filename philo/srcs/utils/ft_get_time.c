/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:57:56 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:15:35 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	long			now;
	struct timeval	va;

	gettimeofday(&va, NULL);
	now = va.tv_sec * 1000;
	now += va.tv_usec / 1000;
	return (now);
}
