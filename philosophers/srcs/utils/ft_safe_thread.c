/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:13:57 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/16 19:22:03 by aaespino         ###   ########.fr       */
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
		ft_error ("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (ENOMEM == status)
		ft_error ("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		ft_error ("Mutex is locked.");
}

void	ft_safe_thread(t_thread *thread, t_pthread_code code)
{
	if (CREATE == code)
		handle_error(pthread_create(thread), code);
	if (JOIN == code)
		handle_error(pthread_join(thread)), code);
	if (DETACH == code)
		handle_error(pthread_detach(thread, NULL), code);
	else
		ft_error("Wrong code for ft_safe_thread: \n"
			GREEN"use <CREATE> <JOIN> <DETACH>"RESET);
}
