#include "../includes/ft_printf.h"

t_str *makeStr(unsigned long long int num, int size)
{
	t_str	*str;
	size_t	i;

	if (num < 10)
	{
		if (!(str =  (t_str *)ft_memalloc(sizeof(t_str))))
			return (NULL);
		if (!(str->str = (char *)ft_memalloc(size + 1)))
		{
			free(str);
			return (str = NULL);
		}
		str->length = size;
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
	int						i;
	unsigned long long int	res;
	unsigned long long int	dpow;

	if (num < 0)
		num *= -1;
	num -= (int)num;
	i = -1;
	dpow = 1;
	while (++i < precision)
		dpow *= 10;
	res = (unsigned long long int)(num * dpow + 0.5);
	return(makeStr(res, 0));
}