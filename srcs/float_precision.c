/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:13:43 by swynona           #+#    #+#             */
/*   Updated: 2020/02/06 19:13:46 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_str	num_to_str(t_ulli num, int size)
{
	t_str	str;
	size_t	i;

	if (num < 10)
	{
		if (!(str.str = (char *)ft_memalloc(size + 2)))
		{
			str.str = NULL;
			str.length = -1;
			return (str);
		}
		str.length = size + 1;
	}
	else
	{
		str = num_to_str(num / 10, size + 1);
		if (!str.str)
			return (str);
	}
	i = 0;
	while ((str.str)[i])
		i++;
	str.str[i] = num % 10 + '0';
	return (str);
}

int		leading_zeros(int pre, long double *num)
{
	int zero_count;
	int	i;

	if (pre > 20)
		return (0);
	zero_count = 0;
	i = -1;
	while (pre - (++i) > 19)
		if ((t_ulli)(((*num) *= 10) + 0.00000003) == 0)
			zero_count++;
	return (zero_count);
}

t_str	precision(int pre, long double num)
{
	int		i;
	t_ulli	res;
	t_ulli	dpow;
	t_str	str;
	int		zero_count;

	num -= (t_ulli)num;
	zero_count = num == 0 ? 0 : leading_zeros(pre, &num);
	i = -1;
	if ((dpow = 1) && num != 0)
		while (++i < (pre > 19 ? 19 : pre) && (dpow *= 10))
			if ((t_ulli)((num * dpow) + 0.00000003) == 0)
				zero_count++;
	res = (t_ulli)(num * dpow + 0.5);
	str = num_to_str(res, 0);
	if (str.str && zero_count != 0 && (t_ulli)(num * dpow + 0.5) > 0)
	{
		clean_strjoin_left(&(str.str), 1, make_str(zero_count, '0'));
		str.length += zero_count;
	}
	if (str.length != -1 && pre - str.length > 0)
		clean_strjoin_right(&(str.str), 1, make_str(pre - str.length, '0'));
	if (str.length < pre)
		str.length = pre;
	return (str);
}
