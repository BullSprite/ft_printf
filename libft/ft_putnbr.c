/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:12:30 by swynona           #+#    #+#             */
/*   Updated: 2019/09/08 18:44:45 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_rec(unsigned int n, char sign)
{
	if (n < 10)
	{
		if (sign)
			ft_putchar('-');
	}
	else
		ft_putnbr_rec(n / 10, sign);
	ft_putchar(n % 10 + '0');
}

void		ft_putnbr(int n)
{
	ft_putnbr_rec(n < 0 ? -n : n, n < 0 ? 1 : 0);
}
