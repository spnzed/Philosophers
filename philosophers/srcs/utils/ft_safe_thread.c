/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:13:57 by aaespino          #+#    #+#             */
/*   Updated: 2023/11/17 14:14:36 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_error(int status, t_pthread_code code)
{
	(!status)
		return ;
	if (EAGAIN == status)
		ft_error ("Thread creation failed: resource or limit issue.");
	else if (EPERM == status)
		ft_error ("Caller lacks permission to set scheduling parameters.");
	else if (EINVAL == status)
	{
		if (CREATE == code)
			ft_error ("The value specified by attr is invalid.");
		else if (JOIN == code || DETACH == code)
			ft_error ("Thread value doesn't refer to a joinable thread.");
	}
	else if (ESRCH == status)
		ft_error ("No thread found for the specified thread ID.");
	else if (EDEADLK == status)
		ft_error ("Deadlock detected or thread value is the calling thread.");
}

void	ft_safe_thread(t_thread *thread, void *(*function)(void *), void *data, 
						t_pthread_code code)
{
	if (CREATE == code)
		handle_error(pthread_create(thread, NULL, function, data), code);
	if (JOIN == code)
		handle_error(pthread_join(*thread, NULL), code);
	if (DETACH == code)
		handle_error(pthread_detach(*thread, NULL), code);
	else
		ft_error("Wrong code for ft_safe_thread: \n"
			GREEN"use <CREATE> <JOIN> <DETACH>"RESET);
}
