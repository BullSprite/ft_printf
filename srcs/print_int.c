/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:27:36 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:27:39 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned long long	int_len(unsigned long long n, int base)
{
	unsigned long long len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

void				int_to_base(unsigned long long n, char base, t_str *res)
{
	size_t	len;
	char	*base_str;

	base_str = "0123456789ABCDEF";
	len = n == 0 ? 1 : int_len(n, base);
	res->str = ft_strnew(len);
	res->length = len;
	while (n >= (t_ulli)base)
	{
		res->str[len - 1] = base_str[n % base];
		len--;
		n /= base;
	}
	res->str[len - 1] = base_str[n % base];
}

int					set_base(char c)
{
	if (c == 'x' || c == 'X')
		return (16);
	else if (c == 'o')
		return (8);
	else
		return (10);
}

t_str				print_unsigned(t_format *format)
{
	unsigned long long	to_print;
	int					base;
	t_str				ret;

	to_print = handle_unsigned_length(format);
	ret.sign = '+';
	base = set_base(format->conversion);
	int_to_base(to_print, base, &ret);
	if (format->conversion == 'x')
		to_lower_str(ret.str);
	if (ret.str[0] == '0')
		handle_int_precision(format, &ret);
	else
	{
		handle_int_precision(format, &ret);
		if (format->flags_set & FLAGS_HASH && ft_strchr("xX",
				format->conversion))
		{
			clean_strjoin_left(&(ret.str),
					1, ft_strdup(format->conversion == 'x' ? "0x" : "0X"));
			ret.length += 2;
		}
	}
	return (ret);
}

t_str				print_int(t_format *format)
{
	long long	to_print;
	t_str		ret;

	if (ft_strchr("uoxX", format->conversion))
		return (print_unsigned(format));
	to_print = handle_length(format);
	ret.sign = to_print >= 0 ? '+' : '-';
	int_to_base(to_print > 0 ? to_print : -1 * to_print, 10, &ret);
	handle_int_precision(format, &ret);
	return (ret);
}
