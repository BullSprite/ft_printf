/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:43 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:51:44 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	handle_sign(t_format *format, t_str *str)
{
	if (format->flags_set & FLAGS_SPACE
		|| format->flags_set & FLAGS_PLUS
		|| str->sign == '-')
		(str->length)++;
}

char	*handle_flag(char *c, t_format *format)
{
	if (*c == '#')
		format->flags_set |= FLAGS_HASH;
	else if (*c == '+')
		format->flags_set |= FLAGS_PLUS;
	else if (*c == '-')
		format->flags_set |= FLAGS_MINUS;
	else if (*c == ' ')
		format->flags_set |= FLAGS_SPACE;
	else if (*c == '0')
		format->flags_set |= FLAGS_ZERO;
	return (*c ? ++c : c);
}

char	*handle_width(char *c, t_format *format, t_utils *s)
{
	if (*c == '*')
	{
		if ((format->width = va_arg(*(format->data), int)) < 0)
		{
			format->width *= -1;
			format->flags_set |= FLAGS_MINUS;
		}
		format->flags_set |= FLAGS_STAR;
		s->first_star = c;
	}
	else if (*c >= '0' && *c <= '9')
	{
		format->width = ft_atoi(c);
		while (*c >= '0' && *c <= '9')
			++c;
		return (c);
	}
	return (*c ? ++c : c);
}

char	*handle_precision(char *c, t_format *format, t_utils *s)
{
	if (*c == '*')
	{
		format->precision = va_arg(*(format->data), int);
		format->flags_set |= FLAGS_STAR;
		s->first_star = c;
	}
	else if (*c >= '0' && *c <= '9')
	{
		format->precision = ft_atoi(c);
		while (*c >= '0' && *c <= '9')
			++c;
		return (c);
	}
	else
		return (c);
	return (*c ? ++c : c);
}

char	*handle_conversion(char *c, t_format *format, t_utils *s)
{
	char *start;
	char *len;

	start = c;
	len = 0;
	if (ft_strchr("lhL", *c))
	{
		while (ft_strchr("lhL", *c))
			++c;
		len = ft_strnew(c - start);
		ft_strncpy(len, start, c - start);
	}
	if (!strchr("fcspdiouxX%", *c))
	{
		(s->error) = 1;
		return (++c);
	}
	format->length = len;
	format->conversion = *c;
	validate_flags(format);
	(s->count) += print_flags(format);
	return (*c ? ++c : c);
}
