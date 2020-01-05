#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	t_format *f = ft_memalloc(sizeof(t_format));
	f->length = "f";
	f->precision = 200;
	f->width = 10;
	f->data = ap;
	t_str *str = type_float(f);
	ft_putstr(str->str);
	va_end(ap);
	return (str->length);
}
