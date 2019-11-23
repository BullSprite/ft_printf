/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:48:52 by swynona           #+#    #+#             */
/*   Updated: 2019/09/16 20:04:35 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	make_res(char **str, char **line, int fd, int ret)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len])
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_strsub(*str, 0, len);
		tmp = ft_strdup((*str) + len + 1);
		ft_strdel(&(*str));
		if (*tmp)
			*str = tmp;
		else
			ft_strdel(&tmp);
	}
	else if (!(*str)[len])
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char		*str[255];
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		if (!(str[fd]) && !(str[fd] = ft_strnew(0)))
			return (-1);
		else if (!(tmp = ft_strjoin(str[fd], buf)))
			return (-1);
		ft_strdel(&(str[fd]));
		str[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (str[fd] == NULL || str[fd][0] == 0))
		return (0);
	return (make_res(&(str[fd]), line, fd, ret));
}
