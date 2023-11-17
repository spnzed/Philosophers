/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:13:57 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/17 14:12:22 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_error(int status, t_pthread_code code)
{
	if (!status)
		return ;
	else if (EINVAL == status)
	{
		if (LOCK == code || UNLOCK == code)
			ft_error ("The value specified by mutex is invalid.");
		if (INIT == code)
			ft_error ("The value specified by attr is invalid.");
	}
	else if (EPERM == status)
		ft_error ("The current thread does not hold a lock on mutex.");
	else if (EDEADLK == status)
		ft_error ("Deadlock possible if thread blocked waits for mutex.");
	else if (ENOMEM == status)
		ft_error ("Insufficient memory to create a new mutex.");
	else if (EBUSY == status)
		ft_error ("Mutex is locked.");
}

void	ft_safe_mutex(t_mutex *mutex, t_pthread_code code)
{
	if (LOCK == code)
		handle_error(pthread_mutex_lock(mutex), code);
	if (UNLOCK == code)
		handle_error(pthread_mutex_unlock(mutex), code);
	if (INIT == code)
		handle_error(pthread_mutex_init(mutex, NULL), code);
	if (DESTROY == code)
		handle_error(pthread_mutex_destroy(mutex), code);
	else
		ft_error("Wrong code for ft_safe_mutex: \n"
			GREEN"use <LOCK> <UNLOCK> <INIT> <DESTROY>"RESET);
}
