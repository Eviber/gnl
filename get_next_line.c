/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 12:52:57 by ygaude            #+#    #+#             */
/*   Updated: 2017/02/24 21:13:54 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

static t_list	*get_buf(const int fd, t_list *list)
{
	while (list)
	{
		if ((int)list->content_size == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static int		read_next_line(const int fd, char **line, char *buf)
{
	ssize_t		len;
	char		*tmp;

	len = 1;
	ft_strappend(line, buf);
	tmp = ft_strchr(buf, '\n');
	while (!tmp && (len = read(fd, buf, BUFF_SIZE)))
	{
		if (len == -1)
			return (-1);
		buf[len] = '\0';
		ft_strappend(line, buf);
		tmp = ft_strchr(buf, '\n');
	}
	if (!ft_strlen(*line) && !len)
		return (0);
	if (!tmp)
		tmp = buf;
	else
	{
		ft_memmove(buf, tmp + 1, ft_strlen(tmp));
		tmp = ft_strchr(*line, '\n');
	}
	*tmp = '\0';
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_list	*list = NULL;
	t_list			*tmp;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_strnew(0);
	tmp = get_buf(fd, list);
	buf = tmp ? ft_strdup((char *)tmp->content) : NULL;
	if (!buf)
	{
		buf = ft_strnew(BUFF_SIZE + 1);
		if (!buf)
			return (-1);
		tmp = ft_lstnew((void *)buf, (size_t)fd);
		if (!tmp)
			return (-1);
		ft_lstadd(&list, tmp);
	}
	ret = read_next_line(fd, line, buf);
	ft_memdel(&(tmp->content));
	tmp->content = buf;
	return (ret);
}
