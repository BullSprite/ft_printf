/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:18:28 by swynona           #+#    #+#             */
/*   Updated: 2020/02/06 19:18:28 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>

# define FLAGS_ZERO 1
# define FLAGS_MINUS 2
# define FLAGS_PLUS 4
# define FLAGS_SPACE 8
# define FLAGS_HASH 16
# define FLAGS_PRECISION 1024
# define FLAGS_STAR 2048
# define TRUE_MASK 4095
# define ULLI unsigned long long int
# define LLI long long int

typedef struct		s_format {
	long long		width;
	long long		precision;
	char			conversion;
	char			*length;
	va_list			*data;
	unsigned	int	flags_set;
	char			hex_zero;
}					t_format;

typedef struct		s_str
{
	char			*str;
	int				length;
	char			sign;
	char			null_term;
}					t_str;

typedef struct		s_utils
{
	int				count;
	int				error;
	char			*first_star;
	int				only_spaces;
	char			*temp;
	char			*start;
}					t_utils;

typedef struct		s_print
{
	char			*left_part;
	char			*right_part;
}					t_print;

int					ft_printf(const char *format, ...);
void				handle_sign(t_format *format, t_str *str);
char				*handle_flag(char *c, t_format *format);
int					print_flags(t_format *format);
char				*handle_width(char *c, t_format *format, t_utils *s);
char				*handle_precision(char *c, t_format *format, t_utils *s);
char				*handle_conversion(char *c, t_format *format, t_utils *s);
void				validate_flags(t_format *format);
void				validate_flags1(t_format *format);
int					parse(char *to_parse, t_format *format, va_list *va,
					t_utils *utils);
int					handle_int_precision(t_format *format, t_str *in);
void				handle_str_precision(t_format *format, t_str *in);
ULLI				handle_unsigned_length(t_format *format);
LLI					handle_length(t_format *format);
t_str				precision(int pre, long double num);
t_str				num_to_str(ULLI num, int size);
t_str				print_int(t_format *format);
t_str				print_float(t_format *format);
t_str				print_string(t_format *format);
t_str				print_pointer(t_format *format);
t_str				print_percent();
char				*make_str(long len, char c);
void				clean_strjoin_left(char **result, int count, ...);
void				clean_strjoin_right(char **result, int count, ...);
void				to_lower_str(char *str);
void				clear_format(t_format *f);
int					print_flags(t_format *format);
#endif
