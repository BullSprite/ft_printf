/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:28:00 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:28:02 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
	f.length = 0;
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
