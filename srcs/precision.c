#include "../includes/ft_printf.h"

t_str num_to_str(ULLI num, int size)
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

t_str prescision(int precision, long double num)
{
	int		i;
	ULLI	res;
	t_str	str;
	int		zero_count;

	num -= (ULLI)num;
	zero_count = 0;
	i = -1;
	if (num != 0)
		while (++i < (precision > 20? 20 : precision))
			if ((ULLI)((num *= 10) + 0.00000003) == 0)
				zero_count++;
	res = (ULLI)(num + 0.5);
	str = num_to_str(res, 0);
	if (str.str && zero_count != 0 && (ULLI)(num + 0.5) > 0)
	{
		clean_strjoin_left(&(str.str), 1, make_str(zero_count, '0'));
		str.length += zero_count;
	}
	if (str.length != -1 && precision - str.length > 0)
		clean_strjoin_right(&(str.str), 1, make_str(precision - str.length, '0'));
	if (str.length < precision)
		str.length = precision;
	return(str);
}