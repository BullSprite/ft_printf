/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:47:09 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:47:13 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	append_sign_m(t_print *p, t_str *in, t_format *format)
{
	if (in->sign == '-')
		clean_strjoin_left(&(p->right_part), 1, ft_strdup("-"));
	else if (format->flags_set & FLAGS_PLUS)
		clean_strjoin_left(&(p->right_part), 1, ft_strdup("+"));
	else if (format->flags_set & FLAGS_SPACE)
		clean_strjoin_left(&(p->right_part), 1, ft_strdup(" "));
}

void	append_sign(t_print *p, t_str *in, t_format *format)
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
	if (p.right_part)
		free(p.right_part);
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
		res = print_percent();
	return (res);
}

int		print_flags(t_format *format)
{
	t_str	ret;
	t_print	p;

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
	ret.length +=
			(format->width - ret.length) > 0 ? format->width - ret.length : 0;
	write_flags(p, format, ret);
	return (ret.length);
}
