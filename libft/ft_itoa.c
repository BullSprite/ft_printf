/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:36:49 by swynona           #+#    #+#             */
/*   Updated: 2019/09/08 17:55:16 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_rec(int n, int size, char sign)
{
	unsigned int	num;
	char			*res;
	size_t			i;

	if (n < 0)
		sign = 1;
	num = n < 0 ? -n : n;
	if (num < 10)
	{
		if (!(res = (char *)ft_memalloc(size + 1 + sign)))
			return (NULL);
		if (sign)
			res[0] = '-';
	}
	else if (!(res = ft_itoa_rec(num / 10, size + 1, sign)))
		return (NULL);
	i = 0;
	while (res[i])
		i++;
	res[i] = num % 10 + '0';
	return (res);
}

char		*ft_itoa(int n)
{
	return (ft_itoa_rec(n, 1, 0));
}
