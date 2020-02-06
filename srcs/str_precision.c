/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:40:16 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 18:40:17 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				handle_str_precision(t_format *format, t_str *in)
{
	size_t	len;

	if (format->conversion == 'c')
	{
		in->length = 1;
		len = 1;
		if (!(in->str[0]))
			return ;
	}
	else
		len = ft_strlen(in->str);
	if (format->precision >= 0 && (t_ulli)format->precision < len)
	{
		(in->str)[format->precision] = 0;
		in->length = format->precision;
	}
	else
		in->length = len;
}
