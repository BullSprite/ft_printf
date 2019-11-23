/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:27:50 by swynona           #+#    #+#             */
/*   Updated: 2019/09/08 14:45:01 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t size1;
	size_t size2;

	size1 = ft_strlen(s1) + 1;
	size2 = ft_strlen(s2) + 1;
	return (ft_memcmp(s1, s2, size1 > size2 ? size1 : size2));
}
