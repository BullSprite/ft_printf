/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 22:28:15 by swynona           #+#    #+#             */
/*   Updated: 2019/09/07 16:02:49 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
		while (++i <= len)
			((unsigned char *)dst)[len - i] = ((unsigned char *)src)[len - i];
	return (dst);
}
