/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <swynona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:57:30 by swynona           #+#    #+#             */
/*   Updated: 2019/09/08 14:32:18 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	while (i < n - 1 && ((unsigned char*)s1)[i] == ((unsigned char*)s2)[i])
		i++;
	return ((int)(((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]));
}
