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
	ULLI	dpow;
	t_str	str;

	if (num < 0)
		num *= -1;
	num -= (ULLI)num;
	i = -1;
	dpow = 1;
	if (num != 0)
		while (++i < (precision > 19? 19 : precision))
			dpow *= 10;
	res = (ULLI)(num * dpow + 0.5);
	str = num_to_str(res, 0);
	if (str.length != -1 && precision - str.length > 0)
		clean_strjoin_right(&(str.str), 1, make_str(precision - str.length, '0'));
	if (str.length < precision)
		str.length = precision;
	return(str);
}