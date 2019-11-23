/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:57:34 by swynona           #+#    #+#             */
/*   Updated: 2019/09/12 19:10:11 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	unsigned char	a;
	unsigned char	b;

	a = (unsigned char)c;
	if (a < 128)
	{
		write(1, &c, 1);
		return ;
	}
	b = (a >> 6) + 0xC0;
	write(1, &b, 1);
	b = ((unsigned char)(a << 2) >> 2) + 0x80;
	write(1, &b, 1);
}
