/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:11:24 by swynona           #+#    #+#             */
/*   Updated: 2019/09/07 20:41:38 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*res;
	size_t	i;
	size_t	l;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	l = ft_strlen(s) - 1;
	while (l != 0 && (s[l] == ' ' || s[l] == '\n' || s[l] == '\t'))
		l--;
	if (!(res = (char *)ft_memalloc((l > i ? ++l - i + 1 : 1) *
			sizeof(char))))
		return (NULL);
	while (i < l)
	{
		res[j] = s[i];
		j++;
		i++;
	}
	return (res);
}
