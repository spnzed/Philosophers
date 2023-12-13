/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:03 by aaespino          #+#    #+#             */
/*   Updated: 2023/12/13 16:55:30 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

long	get_time(void);

int	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
	return (0);
}

long	get_time(void)
{
	long		now;
	struct timeval	va;

	gettimeofday(&va, NULL);
	now = va.tv_sec * 1000;
	now += va.tv_usec / 1000;
	return (now);
}
