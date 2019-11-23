/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:04:48 by swynona           #+#    #+#             */
/*   Updated: 2019/09/05 21:10:01 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	save;

	i = -1;
	save = -1;
	while (s[++i])
		if (s[i] == (char)c)
			save = i;
	if (c == 0)
		return ((char *)(s + i));
	if (save == -1)
		return (NULL);
	return ((char *)(s + save));
}
