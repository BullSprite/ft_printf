/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:15:33 by swynona           #+#    #+#             */
/*   Updated: 2020/02/06 19:15:34 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_str	make_float(t_format *format, long double num, char sign)
{
	t_str	pre;
	t_str	str;

	pre = precision(format->precision, num);
	if (pre.length > format->precision && (pre.str)[0] == '1')
	{
		(pre.str)[0] = '0';
		num += 1;
		pre.length--;
		(pre.str)[pre.length] = 0;
	}
	str = num_to_str((t_ulli)(num < 0 ? -num : num), 1);
	str.sign = sign;
	str.str[str.length - 1] = '.';
	clean_strjoin_right(&(str.str), 1, pre.str);
	str.length += pre.length;
	return (str);
}

t_str	print_float(t_format *format)
{
	long double	num;
	t_str		str;
	char		sign;

	if (format->precision == -1)
		format->precision = 6;
	if ((format->length) && !ft_strcmp("L", format->length))
		num = va_arg(*(format->data), long double);
	else
		num = va_arg(*(format->data), double);
	sign = num < 0 ? '-' : '+';
	num = num < 0 ? -num : num;
	if (format->precision == 0)
	{
		str = num_to_str(num + 0.5, (format->flags_set & FLAGS_HASH) ? 1 : 0);
		if (format->flags_set & FLAGS_HASH)
			str.str[str.length - 1] = '.';
		str.sign = sign;
		return (str);
	}
	str = make_float(format, num, sign);
	return (str);
}
