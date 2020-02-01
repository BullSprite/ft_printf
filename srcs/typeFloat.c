#include "../includes/ft_printf.h"

char *ft_strjoin_tofirst(char *s1, const char *s2)
{
	char	*res;
	char 	*tmp;
	size_t	size;

	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	else if (s1)
		size = ft_strlen(s1) + 1;
	else if (s2)
		size = ft_strlen(s2) + 1;
	else
		return (NULL);
	tmp = s1;
	if (!(res = (char *)ft_memalloc(size * sizeof(char))))
		return (NULL);
	if (s1)
		res = ft_strcpy(res, s1);
	if (s2)
		res = ft_strcat(res, s2);
	free(tmp);
	return (res);
}

char *ft_strjoin_tosecond(const char *s1, char *s2)
{
	char	*res;
	char 	*tmp;
	size_t	size;

	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	else if (s1)
		size = ft_strlen(s1) + 1;
	else if (s2)
		size = ft_strlen(s2) + 1;
	else
		return (NULL);
	tmp = s2;
	if (!(res = (char *)ft_memalloc(size * sizeof(char))))
		return (NULL);
	if (s1)
		res = ft_strcpy(res, s1);
	if (s2)
		res = ft_strcat(res, s2);
	free(tmp);
	return (res);
}

t_str	*type_float(t_format *format)
{
	float	num;
	t_str	*pre;
	t_str	*str;
	char	*st;

	num = va_arg(*(format->data), double);
	pre = prescision(format->precision, num);
	str = (t_str*)ft_memalloc(sizeof(t_str));
	str->str = ft_strjoin(num_to_str((ULLI)(num < 0 ? -num : num),
			format->width), '.');
	str->str = ft_strjoin(str->str, pre->str);
	free(pre->str);
	str->length = 1 + pre->length;
	free(pre);
	return (str);
}