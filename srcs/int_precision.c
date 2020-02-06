/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:36:23 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 18:36:24 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				handle_hex(t_format *format, t_str *in)
{
	if ((in->str[0]) == '0' && format->hex_zero)
		format->precision += 2;
}

int					handle_int_precision1(t_format *format, t_str *in)
{
	if (format->conversion == 'o' && (format->flags_set & FLAGS_HASH))
	{
		if ((in->str[0]) == '0')
		{
			in->length = 1;
			in->str[0] = '0';
		}
		else
		{
			clean_strjoin_left(&(in->str), 1,
					make_str(1, '0'));
			in->length += 1;
		}
	}
	if ((format->precision) > (in->length))
	{
		clean_strjoin_left(&(in->str), 1,
				make_str(format->precision - in->length, '0'));
		in->length += format->precision - in->length;
	}
	return (format->conversion == 'o' ? 0 : 1);
}

int					handle_int_precision(t_format *format, t_str *in)
{
	handle_hex(format, in);
	if (!(format->precision) && (in->str[0]) == '0')
	{
		in->length = 0;
		free(in->str);
		if (!(in->str = ft_strnew(1)))
			return (0);
		if (format->conversion == 'o' && format->flags_set & FLAGS_HASH)
		{
			in->length = 1;
			in->str[0] = '0';
		}
		return (0);
	}
	return (handle_int_precision1(format, in));
}
