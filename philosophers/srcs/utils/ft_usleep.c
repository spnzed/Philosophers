/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:03 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/23 16:49:46 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	struct timeval	va;

	start = gettimeofday(&va, NULL);
	while ((gettimeofday(&va, NULL) - start) < time)
		usleep(50);
	return (0);
}
