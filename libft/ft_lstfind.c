/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:26:46 by swynona           #+#    #+#             */
/*   Updated: 2019/09/12 20:40:03 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list **alst, void const *content, size_t content_size)
{
	t_list	*node;

	node = NULL;
	if (alst)
	{
		node = *alst;
		while (node && ft_memcmp(node->content, content, content_size))
			node = node->next;
	}
	return (node ? node : NULL);
}
