#include "../includes/ft_printf.h"

t_str *makeStr(ULLI num, int size, int sign, int maxsize)
{
	t_str	*str;
	size_t	i;

	if (num < 10 || (maxsize != -1 && size == maxsize))
	{
		if (!(str =  (t_str *)ft_memalloc(sizeof(t_str))))
			return (NULL);
		if (!(str->str = (char *)ft_memalloc(size + 1 + sign)))
		{
			free(str);
			return (str = NULL);
		}
		str->length = size + sign;
		if (sign == 1)
			str->str[0] = '-';
	}
	else if (!(str = makeStr(num / 10, size + 1)))
		return (NULL);
	i = 0;
	while ((str->str)[i])
		i++;
	str->str[i] = num % 10 + '0';
	return (str);
}

t_str *prescision(int precision, double num)
{
	int		i;
	ULLI	res;
	ULLI	dpow;

	if (num < 0)
		num *= -1;
	num -= (int)num;
	i = -1;
	dpow = 1;
	while (++i < precision && (num * dpow) != (ULLI)(num * dpow))
		dpow *= 10;
	res = (ULLI)(num * dpow + 0.5);
	return(makeStr(res, 0, 0, -1));
}