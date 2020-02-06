/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:53:04 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/06 18:53:05 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*make_str(long len, char c)
{
	char	*temp;
	int		i;

	if (len <= 0)
		return (0);
	i = -1;
	if (!(temp = ft_strnew(len)))
		return (0);
	while (++i < len)
		temp[i] = c;
	return (temp);
}

void	clean_strjoin_left(char **result, int count, ...)
{
	va_list	va;
	char	*temp;
	char	*temp1;

	va_start(va, count);
	while (count-- > 0)
	{
		temp = *result;
		temp1 = va_arg(va, char *);
		if (!temp1)
			return ;
		if (!temp)
			*result = temp1;
		else
		{
			*result = ft_strjoin(temp1, *result);
			free(temp);
			free(temp1);
		}
	}
	va_end(va);
}

void	clean_strjoin_right(char **result, int count, ...)
{
	va_list	va;
	char	*temp;
	char	*temp1;

	va_start(va, count);
	while (count-- > 0)
	{
		temp = *result;
		temp1 = va_arg(va, char *);
		*result = ft_strjoin(*result, temp1);
		free(temp);
		free(temp1);
	}
	va_end(va);
}

void	to_lower_str(char *str)
{
	while (*str)
	{
		if (*str <= 'Z' && *str >= 'A')
			*str += 'a' - 'A';
		(str)++;
	}
}

void	clear_format(t_format *f)
{
	f->width = -1;
	f->precision = -1;
	if (f->length)
	{
		free(f->length);
		f->length = 0;
	}
	else
		f->length = 0;
	f->flags_set = 0;
	f->data = NULL;
	f->conversion = 0;
	f->hex_zero = 0;
}
