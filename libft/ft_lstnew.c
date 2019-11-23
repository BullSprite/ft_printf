/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:31:38 by swynona           #+#    #+#             */
/*   Updated: 2019/09/09 19:27:16 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memdup_loc(const void *src, size_t size)
{
	void	*res;

	if (!(res = ft_memalloc(size)))
	{
		res = NULL;
		return (NULL);
	}
	ft_memcpy(res, src, size);
	return (res);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if (!(node = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		node = NULL;
		return (NULL);
	}
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		if (!(node->content = ft_memdup_loc(content, content_size)))
		{
			free(node);
			node = NULL;
			return (NULL);
		}
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
