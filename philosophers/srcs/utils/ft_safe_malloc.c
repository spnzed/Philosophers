/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaronespinosa <aaronespinosa@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:52:42 by aaronespino       #+#    #+#             */
/*   Updated: 2023/11/13 22:55:08 by aaronespino      ###   ########.fr       */
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
