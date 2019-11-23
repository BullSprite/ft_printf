/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:50:01 by swynona           #+#    #+#             */
/*   Updated: 2019/09/13 18:15:01 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_skip(char const *s, char c, size_t i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static size_t	ft_non_split_skip(char const *s, char c, size_t i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		i = ft_split_skip(s, c, i);
		if (s[i] && ++count)
			i = ft_non_split_skip(s, c, i);
	}
	return (count + 1);
}

static void		*ft_del(char **s, size_t n, size_t inside)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (inside)
	{
		while (i < n)
		{
			j = 0;
			while (s[i][j])
				s[i][j] = 0;
			free(s[i]);
			s[i] = NULL;
		}
	}
	free(s);
	s = NULL;
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s)
		return (NULL);
	k = 0;
	if (!(res = (char **)ft_memalloc(ft_word_count(s, c) * sizeof(char *))))
		return (ft_del(res, 1, 0));
	j = 0;
	while (s[i = ft_split_skip(s, c, j)])
	{
		j = ft_non_split_skip(s, c, i);
		if (!(res[k] = (char *)ft_memalloc((j - i + 1) * sizeof(char))))
			return (ft_del(res, k, 1));
		res[k] = ft_strncpy(res[k], s + i, j - i);
		k++;
	}
	return (res);
}
