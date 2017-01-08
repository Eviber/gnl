/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 12:52:57 by ygaude            #+#    #+#             */
/*   Updated: 2017/01/08 23:59:27 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

void	ft_strappend(char **s1, char *s2)
{
	char	*tmp;

	if (!*s1 || !s2)
		return ;
	tmp = ft_strjoin(*s1, s2);
	ft_strdel(s1);
	*s1 = tmp;
}

t_list	*get_buf(const int fd, t_list *list)
{
	while (list)
	{
		if ((int)list->content_size == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int		read_next_line(const int fd, char **line, char *buf)
{
	ssize_t		len;
	char		*tmp;
	int			check;

	check = 0;
	tmp = ft_strchr(buf, '\n');
	len = 1;
	ft_strappend(line, buf);
	while (!tmp && len && len != -1)
	{
		len = read(fd, buf, BUFF_SIZE);
		if (len)
			check = 1;
		tmp = ft_strchr(buf, '\n');
		ft_strappend(line, buf);
		buf[len] = '\0';
	}
	if (len == -1 || (!len && !check) || !buf)
		return ((!buf) ? -1 : len);
	ft_memmove(buf, tmp + 1, ft_strlen(tmp));
	tmp = ft_strchr(*line, '\n');
	*tmp = '\0';
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_list	*list = NULL;
	t_list			*tmp;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_strnew(1);
	tmp = get_buf(fd, list);
	buf = tmp ? (char *)tmp->content : NULL;
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
	tmp->content = buf;
	return (ret);
}
