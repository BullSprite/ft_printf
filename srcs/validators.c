/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:52:59 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:53:00 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
