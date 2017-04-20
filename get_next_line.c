/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/04/20 19:35:23 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		read_nl(const int fd, char **res, char **buf)
{
	int		ret;
	char	*tmp;

	tmp = NULL;
//	while (!tmp && (ret = read(fd, *buf, 5)))
	{
		if (ret == -1)
			return (-1);
		{
			tmp = ft_strjoin(*res, *buf);
			if (*res)
				free(*res);
			*res = tmp;
		}
		tmp = ft_strchr(*res, '\n');
	}
	return (ret);
/*
	int		ret;
	char	*tmp;
	char	*line_buf;

	line_buf = ft_strdup(*buf);
	tmp = ft_strchr(line_buf, '\n');
	if (!(!tmp && (ret = read(fd, *buf, BUFF_SIZE))))
	{
		if (ret == -1)
			return (-1);
		ft_strappend(&line_buf, *buf);
		tmp = ft_strchr(line_buf, '\n');
	}
	*res = ft_strsub(line_buf, 0, (size_t)(tmp - line_buf));
	tmp = ft_strsub(tmp, 0, ft_strlen(tmp));
	ft_strdel(&line_buf);
	*buf = tmp;
	return (ret || ft_strlen(*buf));
*/
}

int		get_next_line(const int fd, char **line)
{
	static char	*buf = NULL;
	int			res;
	if (!buf)
		buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!buf)
		return (-1);
	res = read_nl(fd, line, &buf);
	ft_putstr(buf);
//	ft_putstr("--->");
//	ft_putendl(*line);
	return (res);
}
