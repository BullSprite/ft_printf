/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:07:05 by swynona           #+#    #+#             */
/*   Updated: 2019/09/13 18:16:23 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lstlen_rec(t_list *node, size_t len)
{
	if (node->next)
		return (ft_lstlen_rec(node->next, len + 1));
	return (len);
}

size_t			ft_lstlen(t_list *alst)
{
	if (alst)
		return (ft_lstlen_rec(alst, 1));
	return (0);
}
