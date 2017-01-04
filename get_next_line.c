/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 12:52:57 by ygaude            #+#    #+#             */
/*   Updated: 2017/01/04 19:57:31 by ygaude           ###   ########.fr       */
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
		return (NULL);
	tmp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = tmp;
}

char	*get_buf(const int fd, t_list *list)
{
	while (list)
	{
		if ((int)list->content_size == fd)
		{
			return ((char *)list->content);
		}
		list = list->next;
	}
	return (NULL);
}

int		read_next_line(const int fd, char **line, char *buf)
{
	ssize_t		len;
	char		*tmp;

	tmp = ft_strchr(buf, '\n');
	len = 1;
	while (!tmp && len && len != -1)
	{
		len = read(fd, buf, BUFF_SIZE);
		tmp = ft_strchr(buf, '\n');
		ft_strappend(line, buf);
		buf[len] = '\0';
	}
	if (len == -1 || (!len && !tmp) || !buf)
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

	if (fd < 0 || !line)
		return (-1);
	*line = ft_strnew(1);
	buf = get_buf(fd, list);
	if (!buf)
	{
		buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (!buf)
			return (-1);
		tmp = ft_lstnew((void *)buf, (size_t)fd);
		if (!tmp)
			return (-1);
		ft_lstadd(&list, tmp);
	}
	else
		*line = ft_strappend(*line, buf);
	return (read_next_line(fd, line, buf));
}

int		main(void)
{
	int		fd;
	int		res;
	char	*str;

	if ((fd = open("test", O_RDONLY)) != -1)
	{
		while ((res = get_next_line(fd, &str)) && res != -1)
		{
			ft_putnbr(res);
			ft_putchar('\n');
			ft_putendl(str);
		}
	//	ft_putnbr(res);
	//	ft_putchar('\n');
	}
	return (0);
}
