/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:57:42 by swynona           #+#    #+#             */
/*   Updated: 2019/09/13 20:15:20 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *src, size_t size)
{
	void *res;

	if (!(res = ft_memalloc(size)))
	{
		res = NULL;
		return (NULL);
	}
	ft_memcpy(res, src, size);
	return (res);
}
