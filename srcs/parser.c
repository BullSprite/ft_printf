/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:40:20 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/13 19:47:53 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	clear_format(t_format *f)
{
	f->width = -1;
	f->precision = -1;
	f->length = 0;
	f->flags_set = 0;
	f->data = NULL;
	f->conversion = 0;
	f->hex_zero = 0;
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

t_str	print_conversion(t_format *format)
{
	t_str res;

	res.str = 0;
	res.length = 0;
	if (format->conversion == 'd' || format->conversion == 'i'
	|| format->conversion == 'o' || format->conversion == 'u'
	|| format->conversion == 'x' || format->conversion == 'X')
		res = print_int(format);
	else if (format->conversion == 's' || format->conversion == 'c')
		res = print_string(format);
	else if (format->conversion == 'p')
		res = print_pointer(format);
	else if (format->conversion == 'f')
		res = print_float(format);
	else if (format->conversion == '%')
		res = print_percent(format);
	return (res);
}

void	validate_flags1(t_format *format)
{
	if ((format->conversion == 'p'
	|| (ft_strchr("xX", format->conversion)
	&& format->flags_set & FLAGS_HASH))
	&& format->precision == -1
	&& format->flags_set & FLAGS_ZERO
	&& !(format->flags_set & FLAGS_MINUS))
	{
		format->precision = format->width - 2;
		format->hex_zero = 1;
		format->width = -1;
	}
	if (format->flags_set & FLAGS_MINUS)
		format->flags_set &= TRUE_MASK - FLAGS_ZERO;
	if (format->flags_set & FLAGS_PLUS)
		format->flags_set &= TRUE_MASK - FLAGS_SPACE;
}

void	validate_flags(t_format *format)
{
	if (!ft_strchr("fpdiuoxX%", format->conversion))
	{
		format->flags_set &= TRUE_MASK - FLAGS_SPACE;
		format->flags_set &= TRUE_MASK - FLAGS_PLUS;
		format->flags_set &= TRUE_MASK - FLAGS_ZERO;
		format->flags_set &= TRUE_MASK - FLAGS_HASH;
	}
	if (ft_strchr("pdiuoxX%", format->conversion) && format->precision > -1)
		format->flags_set &= TRUE_MASK - FLAGS_ZERO;
	if (ft_strchr("oxXu", format->conversion))
	{
		format->flags_set &= TRUE_MASK - FLAGS_SPACE;
		format->flags_set &= TRUE_MASK - FLAGS_PLUS;
	}
	validate_flags1(format);
}

void	append_sign_m(t_print *p, t_str *in, t_format *format)
{
	if (in->sign == '-')
		clean_strjoin_left(&(p->right_part), 1, ft_strdup("-"));
	else if (format->flags_set & FLAGS_PLUS)
		clean_strjoin_left(&(p->right_part), 1, ft_strdup("+"));
	else if (format->flags_set & FLAGS_SPACE)
		clean_strjoin_left(&(p->right_part), 1, ft_strdup(" "));
}

void append_sign(t_print *p, t_str *in, t_format *format)
{
	if (format->flags_set & FLAGS_MINUS)
	{
		append_sign_m(p, in, format);
		return ;
	}
	if (format->flags_set & FLAGS_ZERO)
	{
		if (in->sign == '-')
			clean_strjoin_left(&(p->left_part), 1, ft_strdup("-"));
		else if (format->flags_set & FLAGS_PLUS)
			clean_strjoin_left(&(p->left_part), 1, ft_strdup("+"));
		else if (format->flags_set & FLAGS_SPACE)
			clean_strjoin_left(&(p->left_part), 1, ft_strdup(" "));
	}
	else
	{
		if (in->sign == '-')
			clean_strjoin_right(&(p->left_part), 1, ft_strdup("-"));
		else if (format->flags_set & FLAGS_PLUS)
			clean_strjoin_right(&(p->left_part), 1, ft_strdup("+"));
		else if (format->flags_set & FLAGS_SPACE)
			clean_strjoin_right(&(p->left_part), 1, ft_strdup(" "));
	}
}

void	handle_sign(t_format *format, t_str *str)
{
	if (format->flags_set & FLAGS_SPACE
	|| format->flags_set & FLAGS_PLUS
	|| str->sign == '-')
		(str->length)++;
}

void	write_flags(t_print p, t_format *format, t_str ret)
{
    if (p.left_part)
		write(1, p.left_part, ft_strlen(p.left_part));
	if ((ret.null_term) && format->conversion == 'c')
		write(1, "\0", 1);
	if (p.right_part)
		write(1, p.right_part, ft_strlen(p.right_part));
	if (p.left_part)
		free(p.left_part);
	if(p.right_part)
		free(p.right_part);
}

int print_flags(t_format *format)
{
	t_str ret;
	t_print p;

	ret = print_conversion(format);
	p.right_part = ret.str;
	p.left_part = 0;
	handle_sign(format, &ret);
	if (format->flags_set & FLAGS_MINUS)
	{
		if (format->width > -1 && (format->width - ret.length) > 0)
			clean_strjoin_right(&(p.right_part), 1,
								make_str(format->width - ret.length, ' '));
	}
	else if (format->width > -1 && (format->width - ret.length) > 0)
		clean_strjoin_right(&(p.left_part), 1,
							make_str(format->width - ret.length,
									 format->flags_set & FLAGS_ZERO ? '0' : ' '));
	append_sign(&p, &ret, format);
	ret.length += (format->width - ret.length) > 0 ? format->width - ret.length : 0;
	write_flags(p, format, ret);
	return (ret.length);
}

char	*handle_conversion(char *c, t_format *format, t_utils *s)
{
	char *start;
	char *len;

	start = c;
	len = 0;
	if (strchr("lhL", *c))
	{
		while (strchr("lhL", *c))
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

char	*pre_parse_1(char *to_parse, t_format *format, t_utils *utils)
{
	if ((*to_parse >= '0' && *to_parse <= '9') || *to_parse == '*')
		to_parse = handle_width(to_parse, format, utils);
	if (*to_parse == '.')
	{
		if (format->width == -1)
			format->width = 0;
		to_parse = handle_precision(++to_parse, format, utils);
		if (format->precision == -1)
			format->precision = 0;
	}
	return (to_parse);
}

char	*pre_parse(char *to_parse, t_format *format, t_utils *utils)
{
	if ((utils->only_spaces = 1) && *to_parse == '%')
	{
		utils->count++;
		utils->error = 1;
		write(1, to_parse++, 1);
		return (to_parse);
	}
	while (1)
		if (*to_parse == '#' || *to_parse == '-' || *to_parse == '+'
		|| *to_parse == ' ' || *to_parse == '0')
		{
			if (*to_parse != ' ')
				utils->only_spaces = 0;
			to_parse = handle_flag(to_parse, format);
		}
		else if (*to_parse == '%' && utils->only_spaces)
		{
			utils->count++;
			utils->error = 1;
			write(1, to_parse++, 1);
			return (to_parse);
		}
		else
			break ;
	return (pre_parse_1(to_parse, format, utils));
}

void	handle_error(t_format *format, t_utils *utils, char *to_parse)
{
	if (utils->error)
	{
		if (format->flags_set & FLAGS_STAR)
		{
			write(1, utils->start, utils->first_star - utils->start);
			utils->temp = ft_itoa(format->width);
			utils->count += ft_strlen(utils->temp);
			write(1, utils->temp, ft_strlen(utils->temp));
			write(1, utils->first_star + 1,
					to_parse - utils->first_star - 1);
			utils->count += to_parse - utils->start - 1;
		}
		else
		{
			write(1, utils->start, to_parse - utils->start);
			utils->count += to_parse - utils->start;
		}
	}
}

int		parse(char *to_parse, t_format *format, va_list *va, t_utils *utils)
{
	while (*to_parse)
	{
		utils->error = 0;
		clear_format(format);
		if (*to_parse != '%')
		{
			++(utils->count);
			write(1, to_parse++, 1);
			continue ;
		}
		format->data = va;
		utils->start = (char *)to_parse++;
		to_parse = pre_parse(to_parse, format, utils);
		if (utils->error || !(*to_parse))
			continue ;
		to_parse = handle_conversion(to_parse, format, utils);
		handle_error(format, utils, to_parse);
	}
	return (utils->count);
}

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	const char	*p;

	p = str;
	while (maxlen-- > 0 && *p)
		p++;
	return (p - str);
}

int		ft_printf(const char *format, ...)
{
	va_list		va;
	int			ret;
	t_format	f;
	t_utils		utils;

	utils.count = 0;
	utils.error = 0;
	clear_format(&f);
	va_start(va, format);
	if (ft_strnlen(format, 2) == 1 && *format == '%')
		ret = 0;
	else
		ret = parse((char *)format, &f, &va, &utils);
	va_end(va);
	if (f.length)
		free(f.length);
	return (ret);
}