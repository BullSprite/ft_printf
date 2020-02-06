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

void				int_to_base(unsigned long long n, char base, t_str *res)
{
	size_t	len;
	char	*base_str;

	base_str = "0123456789ABCDEF";
	len = n == 0 ? 1 : int_len(n, base);
	res->str = ft_strnew(len);
	res->length = len;
	while (n >= (ULLI)base)
	{
		res->str[len - 1] = base_str[n % base];
		len--;
		n /= base;
	}
	res->str[len - 1] = base_str[n % base];
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

int					set_base(char c)
{
	if (c == 'x' || c == 'X')
		return (16);
	else if (c == 'o')
		return (8);
	else
		return (10);
}

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
	if (format->precision >= 0 && (ULLI)format->precision < len)
	{
		(in->str)[format->precision] = 0;
		in->length = format->precision;
	}
	else
		in->length = len;
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
