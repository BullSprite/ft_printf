#ifndef PRINTF_H
# define PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>

# define FLAGS_ZERO			(1U <<  0U)
# define FLAGS_MINUS		(1U <<  1U)
# define FLAGS_PLUS			(1U <<  2U)
# define FLAGS_SPACE		(1U <<  3U)
# define FLAGS_HASH			(1U <<  4U)
# define FLAGS_UPPERCASE	(1U <<  5U)
# define FLAGS_CHAR			(1U <<  6U)
# define FLAGS_SHORT		(1U <<  7U)
# define FLAGS_LONG			(1U <<  8U)
# define FLAGS_LONG_LONG	(1U <<  9U)
# define FLAGS_PRECISION	(1U << 10U)
# define FLAGS_STAR			(1U << 11U)
# define ULLI				unsigned long long int
# define LLI				long long int

//http://www.cplusplus.com/reference/cstdio/printf/

typedef struct	s_format
{
	int  		width;
	int  		precision;
	char 		conversion;
	char 		*length;
	va_list 	*data;
	unsigned int flags_set;
}				t_format;

typedef struct	s_str
{
	char 		*str;
	int 		length;
}				t_str;

int		ft_printf(const char *format, ...);
t_str 	*prescision(int precision, double num);
t_str 	*width(int wid, int sign, ULLI num);
t_str	*make_str(ULLI num, int size, int sign);
t_str	*type_float(t_format *format);
char	*ft_strjoin_tofirst(char *s1, const char *s2);
char	*ft_strjoin_tosecond(const char *s1, char *s2);
#endif //PRINTF_H
