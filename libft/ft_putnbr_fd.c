/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:50:59 by swynona           #+#    #+#             */
/*   Updated: 2019/09/08 18:52:55 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_rec(unsigned int n, char sign, int fd)
{
	if (n < 10)
	{
		if (sign)
			ft_putchar_fd('-', fd);
	}
	else
		ft_putnbr_fd_rec(n / 10, sign, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_fd_rec(n < 0 ? -n : n, n < 0 ? 1 : 0, fd);
}
