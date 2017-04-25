/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/04/23 19:33:01 by ygaude           ###   ########.fr       */
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

	ret = 1;
	tmp = NULL;
	if (*buf && **buf)
		*res = ft_strdup(*buf);
	tmp = (*res) ? ft_strchr(*res, '\n') : NULL;
	while (!tmp && (ret = read(fd, *buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		{
			tmp = (*res) ? ft_strjoin(*res, *buf) : ft_strdup(*buf);
			if (*res)
				free(*res);
			*res = tmp;
		}
		tmp = NULL;
		tmp = (*res) ? ft_strchr(*res, '\n') : NULL;
	}
	tmp = ft_strchr(*buf, '\n');
	if (tmp)
		*buf = ft_strsub(*buf, tmp - *buf + 1, ft_strlen(tmp));
	tmp = (*res) ? ft_strchr(*res, '\n') : NULL;
	if (tmp)
		*tmp = '\0';
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buf = NULL;
	int			res;

	*line = NULL;
	if (!buf)
		buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!buf)
		return (-1);
	res = read_nl(fd, line, &buf);
	return (res);
}
