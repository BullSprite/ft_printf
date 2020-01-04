#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	t_flag *a = ft_memalloc(sizeof(t_flag));
	a->pres = 4;
	a->data = "abcde";
	a->length = "s";
	return (prescision(a));
}
