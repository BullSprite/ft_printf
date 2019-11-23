/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:31:16 by swynona           #+#    #+#             */
/*   Updated: 2019/09/13 18:20:52 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc(void **data, size_t size, size_t new_size)
{
	void	*newarr;
	size_t	i;

	if (!(newarr = ft_memalloc(new_size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		((unsigned char *)newarr)[i] = ((unsigned char *)(*data))[i];
		((unsigned char *)(*data))[i] = 0;
		i++;
	}
	free(*data);
	*data = ((void *)newarr);
	return (*data);
}
