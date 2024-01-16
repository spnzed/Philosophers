/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:03 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/16 15:32:04 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>


static long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long time)
{
	time += get_time();
	while (get_time() <= time)
		usleep(200);
	return 0;
}


// static long	get_time(void)
// {
// 	long			now;
// 	struct timeval	va;

// 	gettimeofday(&va, NULL);
// 	now = va.tv_sec * 1000;
// 	now += va.tv_usec / 1000;
// 	return (now);
// }

// int	ft_usleep(long time)
// {
// 	long	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(200);
// 	return (0);
// }
