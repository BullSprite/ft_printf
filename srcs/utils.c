#include "../includes/ft_printf.h"

char *make_str(long len, char c)
{
	char *temp;
	int i;

	if (len <= 0)
		return (0);
	i = -1;
	if(!(temp = ft_strnew(len)))
		return (0);
	while (++i < len)
	{
		temp[i] = c;
	}
	return (temp);
}

void clean_strjoin_left(char **result, int count, ...)
{
	va_list va;
	char *temp;
	char *temp1;

	va_start(va, count);
	while(count-- > 0)
	{
		temp = *result;
		temp1 = va_arg(va, char *);
		if (!temp1)
			return ;
		if (!temp)
			*result = temp1;
		else
		{
			*result = ft_strjoin(temp1, *result);
			free(temp);
			free(temp1);
		}
	}
	va_end(va);
}

void clean_strjoin_right(char **result, int count, ...)
{
	va_list va;
	char *temp;
	char *temp1;

	va_start(va, count);
	while(count-- > 0)
	{
		temp = *result;
		temp1 = va_arg(va, char *);
		*result = ft_strjoin(*result, temp1);
		free(temp);
		free(temp1);
	}
	va_end(va);
}

void to_lower_str(char *str)
{
	while (*str)
	{
		if (*str <= 'Z' && *str >= 'A')
			*str += 'a' - 'A';
		(str)++;
	}
}