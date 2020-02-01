#include "../includes/ft_printf.h"

t_str *num_to_str(ULLI num, int size)
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
		str->length = size + 1;
	}
	else if (!(str = num_to_str(num / 10, size + 1)))
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
	t_str	*str;
	char 	*tmp;

	if (num < 0)
		num *= -1;
	num -= (int)num;
	i = -1;
	dpow = 1;
	while (++i < (precision > 19? 19 : precision))
		dpow *= 10;
	res = (ULLI)(num * dpow + 0.5);
	str = num_to_str(res, 0);
	while (str->length < precision)
	{
		tmp = str->str;
		str->str = ft_strjoin(str->str, "0");
		free(tmp);
		str->length++;
	}
	return(str);
}