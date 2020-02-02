/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:40:20 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/13 19:47:53 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//flags to handle #0-+
//conversions : csp
//conversions with l ll h hh : diouxX
//conversions with l L: f
//width and precision - handle int overflow

int sign(t_format *f, char c)
{
    return ((f->flags_set & FLAGS_SPACE ||
    f->flags_set & FLAGS_PLUS)
    && strchr("fpdiouxX", f->conversion) && c != '-');
}
typedef struct s_s {
    int count;
    int error;
    char *first_star;
} s_utils;
typedef struct t_a {
    char *left_part;
    char *right_part;
} s_print;

void clear_format(t_format *f)
{
    f->width = -1;
    f->precision = -1;
    f->length = 0;
    f->flags_set = 0;
    f->data = NULL;
    f->conversion = 0;
}

char    *handle_flag(char *c, t_format *format)
{
    if (*c == '#')
        format->flags_set |= FLAGS_HASH;
    else if (*c == '+')
        format->flags_set |= FLAGS_PLUS;
    else if (*c == '-')
        format->flags_set |= FLAGS_MINUS;
    else if (*c == ' ')
        format->flags_set |= FLAGS_SPACE;
    else if (*c == '0')
        format->flags_set |= FLAGS_ZERO;
    return (++c);
}

char    *handle_width(char *c, t_format *format, s_utils *s)
{
    if (*c == '*')
    {
        format->width = va_arg(*(format->data), int);
        format->flags_set |= FLAGS_STAR;
        s->first_star = c;
    }
    else if (*c >= '0' && *c <= '9')
    {
        //temp solution
        format->width = ft_atoi(c);
        while (*c >= '0' && *c <= '9')
            ++c;
        return (c);
    }
    return (++c);
}

char    *handle_precision(char *c, t_format *format)
{
    if (*c >= '0' && *c <= '9')
    {
        //temp solution
        format->precision = ft_atoi(c);
        while (*c >= '0' && *c <= '9')
            ++c;
        return (c);
    }
    else
        return (c);
    return (++c);
}

t_str print_conversion(t_format *format)
{
    t_str res;

    if (format->conversion == 'd' || format->conversion == 'i'
        || format->conversion == 'o' || format->conversion == 'u'
        || format->conversion == 'x' || format->conversion == 'X')
        res = print_int(format);
    else if(format->conversion == 's' || format->conversion == 'c')
        res = print_string(format);
    else if(format->conversion == 'p')
        res = print_pointer(format);
    else if(format->conversion == 'f')
        res = print_float(format);
    return (res);

}


void validate_flags(t_format *format)
{
    if (!ft_strchr("fpdiuoxX", format->conversion))
    {
        format->flags_set &= TRUE_MASK - FLAGS_SPACE;
        format->flags_set &= TRUE_MASK - FLAGS_PLUS;
        format->flags_set &= TRUE_MASK - FLAGS_ZERO;
        format->flags_set &= TRUE_MASK - FLAGS_HASH;
    }
    if (ft_strchr("pdiuoxX", format->conversion) && format->precision > -1)
		format->flags_set &= TRUE_MASK - FLAGS_ZERO;
    if (ft_strchr("oxX", format->conversion))
    {
        format->flags_set &= TRUE_MASK - FLAGS_SPACE;
        format->flags_set &= TRUE_MASK - FLAGS_PLUS;
        format->flags_set &= TRUE_MASK - FLAGS_ZERO;
    }
    if (format->flags_set & FLAGS_MINUS)
        format->flags_set &= TRUE_MASK - FLAGS_ZERO;
    if (format->flags_set & FLAGS_PLUS)
        format->flags_set &= TRUE_MASK - FLAGS_SPACE;
}

void apppend_sign_m(s_print *p, t_str *in, t_format *format)
{
    if (in->sign == '-')
        clean_strjoin_left(&(p->right_part), 1, ft_strdup("-"));
    else if (format->flags_set & FLAGS_PLUS)
        clean_strjoin_left(&(p->right_part), 1, ft_strdup("+"));
    else if (format->flags_set & FLAGS_SPACE)
        clean_strjoin_left(&(p->right_part), 1, ft_strdup(" "));
}

void append_sign(s_print *p, t_str *in, t_format *format)
{
    if (format->flags_set & FLAGS_MINUS)
    {
        apppend_sign_m(p, in, format);
        return ;
    }
    if (format->flags_set & FLAGS_ZERO)
    {
        if (in->sign == '-')
            clean_strjoin_left(&(p->left_part), 1, ft_strdup("-"));
        else if (format->flags_set & FLAGS_PLUS)
            clean_strjoin_left(&(p->left_part), 1, ft_strdup("+"));
        else if (format->flags_set & FLAGS_SPACE)
            clean_strjoin_left(&(p->left_part), 1, ft_strdup(" "));
    }
    else
    {
        if (in->sign == '-')
            clean_strjoin_right(&(p->left_part), 1, ft_strdup("-"));
        else if (format->flags_set & FLAGS_PLUS)
            clean_strjoin_right(&(p->left_part), 1, ft_strdup("+"));
        else if (format->flags_set & FLAGS_SPACE)
            clean_strjoin_right(&(p->left_part), 1, ft_strdup(" "));
    }
}

void handle_sign(t_format *format, t_str *str)
{
    if (format->flags_set & FLAGS_SPACE
    || format->flags_set & FLAGS_PLUS
    || str->sign == '-')
        (str->length)++;
}
//right part - integer with or without sign
//left part - width with or without sign
int print_flags(t_format *format)
{
    t_str ret;
    s_print p;

    ret = print_conversion(format);
    p.right_part = ret.str;
    p.left_part = ft_strnew(0);
    handle_sign(format, &ret);
    if (format->flags_set & FLAGS_MINUS)
    {
        if (format->width != -1 && (format->width - ret.length) > 0)
            clean_strjoin_right(&(p.right_part), 1,
                          make_str(format->width - ret.length, ' '));
    }
    else
    {
        if (format->width != -1 && (format->width - ret.length) > 0)
            clean_strjoin_right(&(p.left_part), 1,
                               make_str(format->width - ret.length,
                                        format->flags_set & FLAGS_ZERO ? '0' : ' '));
    }
    append_sign(&p, &ret, format);
    ret.length += (format->width - ret.length) > 0 ? format->width - ret.length : 0;
    write(1, p.left_part, ft_strlen(p.left_part));
    write(1, p.right_part, ft_strlen(p.right_part));
    return (ret.length);
}


char    *handle_conversion(char *c, t_format *format, s_utils *s)
{
    char *start;
    char *len;

    start = c;
    if (strchr("lhL", *c))
    {
        while (strchr("lhL", *c))
            ++c;
        len = ft_strnew(c - start);
        ft_strncpy(len, start, c - start);
    }
    if(!strchr("fcspdiouxX", *c))
    {
        (s->error) = 1;
        return (++c);
    }
    format->length = len;
    format->conversion = *c;
    validate_flags(format);
    (s->count) += print_flags(format);
    return (++c);
}

char *pre_parse(char *to_parse, t_format *format, s_utils *utils)
{
    if (*to_parse == '%')
    {
        utils->count++;
        utils->error = 1;
        write(1, to_parse++, 1);
        return (to_parse);
    }
    while (1)
        if (*to_parse == '#' || *to_parse == '-' || *to_parse == '+'
        || *to_parse == ' ' || *to_parse == '0')
            to_parse = handle_flag(to_parse, format);
        else
            break ;
    if ((*to_parse >= '0' && *to_parse <= '9') || *to_parse == '*')
        to_parse = handle_width(to_parse, format, utils);
    if (*to_parse == '.')
        to_parse = handle_precision(++to_parse, format);

    return (to_parse);
}
int parse(char *to_parse, t_format *format, va_list *va, s_utils *utils)
{
    char *start;
    char *temp;

    while (*to_parse)
    {
        utils->error = 0;
        clear_format(format);
        if (*to_parse != '%')
        {
            ++(utils->count);
            write(1, to_parse++, 1);
            continue ;
        }
        format->data = va;
        start = (char *)to_parse++;
        to_parse = pre_parse(to_parse, format, utils);
        if (utils->error)
            continue ;
        to_parse = handle_conversion(to_parse, format, utils);
        if (utils->error)
        {
            if (format->flags_set & FLAGS_STAR)
            {

                write(1, start, utils->first_star - start);
                temp = ft_itoa(format->width);
                utils->count += ft_strlen(temp);
                write(1, temp, ft_strlen(temp));
                write(1, utils->first_star + 1, to_parse - utils->first_star - 1);
                utils->count += to_parse - start - 1;
            }
            else
            {
                write(1, start, to_parse - start);
                utils->count += to_parse - start;
            }
        }
    }
    return (utils->count);
}

size_t ft_strnlen(const char *str, size_t maxlen)
{
    const char *p;

    p = str;

    while (maxlen-- > 0 && *p)
        p++;
    return (p - str);
}

int ft_printf(const char* format, ...)
{
    va_list va;
    int ret;
    t_format f;
    s_utils utils;

    utils.count = 0;
    utils.error = 0;
    va_start(va, format);
    if (ft_strnlen(format, 2) == 1 && *format == '%')
        ret = -1;
    else
        ret = parse((char *)format, &f, &va, &utils);
    va_end(va);
    return (ret);
}


