/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_pointer_percent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:41:23 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 18:41:24 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t				pointer_len(size_t n)
{
	size_t len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void				pointer_to_str(size_t n, t_str *res)
{
	size_t	len;
	char	*base_str;

	base_str = "0123456789abcdef";
	len = pointer_len(n);
	res->str = ft_strnew(len);
	res->length = len;
	while (n > 0)
	{
		res->str[len - 1] = base_str[n % 16];
		len--;
		n /= 16;
	}
}

t_str				print_string(t_format *format)
{
	char	*to_print;
	t_str	ret;

	ret.null_term = 0;
	if (format->conversion == 'c')
	{
		to_print = ft_strnew(1);
		if (!(to_print[0] = va_arg(*(format->data), int)))
			ret.null_term = 1;
		ret.str = to_print;
	}
	else
	{
		if (!(to_print = va_arg(*(format->data), char *)))
			to_print = "(null)";
		ret.str = ft_strdup(to_print);
	}
	handle_str_precision(format, &ret);
	return (ret);
}

t_str				print_pointer(t_format *format)
{
	size_t	to_print;
	t_str	ret;

	if (!(to_print = va_arg(*(format->data), size_t)))
	{
		if (format->precision > 0 || format->precision == -1)
		{
			ret.str = ft_strdup("0");
			ret.length = 1;
			handle_int_precision(format, &ret);
			clean_strjoin_left(&(ret.str), 1, ft_strdup("0x"));
			ret.length += 2;
		}
		else
			ret.str = ft_strdup("0x");
		ret.length = ft_strlen(ret.str);
	}
	else
	{
		pointer_to_str(to_print, &ret);
		handle_int_precision(format, &ret);
		clean_strjoin_left(&(ret.str), 1, ft_strdup("0x"));
		ret.length += 2;
	}
	return (ret);
}

t_str				print_percent(void)
{
	t_str	ret;

	ret.str = ft_strnew(1);
	ret.str[0] = '%';
	ret.length = 1;
	return (ret);
}
