/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:00:24 by swynona           #+#    #+#             */
/*   Updated: 2019/09/07 18:10:56 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	size_t	i;
	char	*res;

	if (!s || !f)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (!(res = (char *)ft_memalloc((size + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (*s)
		res[i++] = f(*s++);
	res[i] = 0;
	return (res);
}
