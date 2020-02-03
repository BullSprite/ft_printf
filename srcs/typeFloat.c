#include "../includes/ft_printf.h"

t_str	print_float(t_format *format)
{
	long double	num;
	t_str		pre;
	t_str		str;

	if (format->precision == -1)
		format->precision = 6;
	if (!ft_strcmp("L", format->length))
		num = va_arg(*(format->data), long double);
	else
		num = va_arg(*(format->data), double);
	pre = prescision(format->precision, num);
	str = num_to_str((ULLI)(num < 0 ? -num : num), 1);
	str.sign = num < 0 ? '-' : '+';
	str.str[str.length - 1] = '.';
	clean_strjoin_right(&(str.str), 1, pre.str);
	str.length += pre.length;
	return (str);
}