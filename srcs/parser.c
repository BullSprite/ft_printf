/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:48:45 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 17:48:46 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
			write(1, utils->first_star + 1, to_parse - utils->first_star - 1);
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
