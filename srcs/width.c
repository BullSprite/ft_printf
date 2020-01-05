#include "../includes/ft_printf.h"

t_str	*width(int wid, int sign, ULLI num)
{
	ULLI	n;

	n = (sign == 0? num : -num);
	return (makeStr(n, 0, sign));
}
