/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:13:57 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:16:57 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	handle_error(int status, t_mutex_code code)
{
	if (!status)
		return (true);
	else if (EINVAL == status)
	{
		if (LOCK == code || UNLOCK == code)
			return (ft_error ("The value specified by mutex is invalid."));
		if (INIT == code)
			return (ft_error ("The value specified by attr is invalid."));
	}
	else if (EPERM == status)
		return (ft_error ("The thread does not hold a lock on mutex."));
	else if (EDEADLK == status)
		return (ft_error ("Deadlock if thread blocked waits for mutex."));
	else if (ENOMEM == status)
		return (ft_error ("Insufficient memory to create a new mutex."));
	else if (EBUSY == status)
		return (ft_error ("Mutex is locked."));
	return (true);
}

bool	ft_safe_mutex(t_mutex *mutex, t_mutex_code code)
{
	if (LOCK == code)
		return (handle_error(pthread_mutex_lock(mutex), code));
	if (UNLOCK == code)
		return (handle_error(pthread_mutex_unlock(mutex), code));
	if (INIT == code)
		return (handle_error(pthread_mutex_init(mutex, NULL), code));
	if (DESTROY == code)
		return (handle_error(pthread_mutex_destroy(mutex), code));
	else
		return (ft_error("Wrong code for ft_safe_mutex: \n"
				GREEN"use <LOCK> <UNLOCK> <INIT> <DESTROY>"RESET));
}
