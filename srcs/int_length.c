/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:37:59 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 18:38:00 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned long long	handle_unsigned_length(t_format *format)
{
	unsigned long long	u_n;

	if (ft_strequ(format->length, "l"))
		u_n = (unsigned long)va_arg(*(format->data), unsigned long);
	else if (ft_strequ(format->length, "ll"))
		u_n = (unsigned long long)va_arg(*(format->data), unsigned long long);
	else if (ft_strequ(format->length, "h"))
		u_n = (unsigned short)va_arg(*(format->data), unsigned int);
	else if (ft_strequ(format->length, "hh"))
		u_n = (unsigned char)va_arg(*(format->data), unsigned int);
	else
		u_n = (unsigned long long)va_arg(*(format->data), unsigned int);
	return (u_n);
}

long long			handle_length(t_format *format)
{
	long long	n;

	if (ft_strequ(format->length, "l"))
		n = (long)va_arg(*(format->data), long);
	else if (ft_strequ(format->length, "ll"))
		n = (long long)va_arg(*(format->data), long long);
	else if (ft_strequ(format->length, "h"))
		n = (short)va_arg(*(format->data), int);
	else if (ft_strequ(format->length, "hh"))
		n = (char)va_arg(*(format->data), int);
	else
		n = (long long)va_arg(*(format->data), int);
	return (n);
}
