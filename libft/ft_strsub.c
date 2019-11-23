/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:24:16 by swynona           #+#    #+#             */
/*   Updated: 2019/09/07 18:43:29 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s || !(res = (char *)ft_memalloc((len + 1) * sizeof(char))))
		return (NULL);
	res = ft_strncpy(res, s + start, len);
	return (res);
}
