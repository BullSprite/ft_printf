#include "../includes/ft_printf.h"

t_str	*typeFloat(t_format *format)
{
	float	num;
	int		pr;
	t_str	*wid;
	t_str	*pre;
	t_str	*str;

	num = va_arg(*(format->data), double);
	wid = width(format->width, num < 0 ? 1 : 0, (ULLI)(num < 0 ? -num : num));
	pr = format->width - wid->length - 1;
	pre = prescision(pr > format->precision ? format->precision : pr, num);
	str = (t_str*)ft_memalloc(sizeof(t_str));
	str->str = ft_strjoin(wid->str, ".");
	free(wid->str);
	wid->str = str->str;
	str->str = ft_strjoin(str->str, pre->str);
	free(wid->str);
	free(pre->str);
	str->length = wid->length + 1 + pre->length;
	free(wid);
	free(pre);
	return (str);
}