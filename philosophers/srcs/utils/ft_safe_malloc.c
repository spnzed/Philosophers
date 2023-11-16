/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:52:42 by aaronespino       #+#    #+#             */
/*   Updated: 2023/11/15 18:41:08 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_safe_malloc(size_t bytes)
{
    void    *ret;

    ret = malloc(bytes);
    if (!ret)
        ft_error("Malloc error");
    return (ret);
}
