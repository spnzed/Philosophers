/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:13:57 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/15 17:22:10 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	handle_error(int status, t_pthread_code code)
{
	if (!status)
		return (true);
	else if (EAGAIN == status)
		return (ft_error ("Thread creation failed: resource or limit issue."));
	else if (EPERM == status)
		return (ft_error ("Lacking permission to set scheduling parameters."));
	else if (EINVAL == status)
	{
		if (CREATE == code)
			return (ft_error ("The value specified by attr is invalid."));
		else if (JOIN == code || DETACH == code)
			return (ft_error ("Value doesn't refer to a joinable thread."));
	}
	else if (ESRCH == status)
		return (ft_error ("No thread found for the specified thread ID."));
	else if (EDEADLK == status)
		return (ft_error ("Deadlock detected, or thread is calling himself."));
	return (true);
}

bool	ft_safe_thread(t_thread *thread, void *(*function)(void *), void *data,
			t_pthread_code code)
{
	if (CREATE == code)
		return (handle_error(pthread_create(thread, NULL,
					function, data), code));
	if (JOIN == code)
		return (handle_error(pthread_join(*thread, NULL), code));
	if (DETACH == code)
		return (handle_error(pthread_detach(*thread), code));
	else
		return (ft_error("Wrong code for ft_safe_thread: \n"
				GREEN"use <CREATE> <JOIN> <DETACH>"RESET));
	return (NULL);
}
