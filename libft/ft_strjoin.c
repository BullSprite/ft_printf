/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:45:11 by swynona           #+#    #+#             */
/*   Updated: 2019/09/07 19:46:43 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	size;

	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	else if (s1)
		size = ft_strlen(s1) + 1;
	else if (s2)
		size = ft_strlen(s2) + 1;
	else
		return (NULL);
	if (!(res = (char *)ft_memalloc(size * sizeof(char))))
		return (NULL);
	if (s1)
		res = ft_strcpy(res, s1);
	if (s2)
		res = ft_strcat(res, s2);
	return (res);
}
