/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 12:52:57 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/12 13:47:22 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

char		*ft_strappend(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*read_ln(int fd)
{
	ssize_t		len;
	static char	*buf = NULL;
	char		*res;
	char		*tmp;

	res = ft_strnew(1);
	tmp = NULL;
	len = 0;
	if (!buf)
		buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	else	
	{
		tmp = ft_strchr(buf, '\n');
		res = ft_strappend(res, buf);
	}
	while (buf && !tmp)
	{
ft_putendl("test");
		len = read(fd, buf, BUFF_SIZE);
		tmp = ft_strchr(buf, '\n');
		res = ft_strappend(res, buf);
		buf[len] = '\0';
	}
	ft_memmove(buf, tmp, ft_strlen(tmp));
	tmp = ft_strchr(res, '\n');
	if (tmp)
		*tmp = '\0';
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	*line = read_ln(fd);
	return (1);
}

int		main(void)
{
	int		fd;
	char	*str;

	if ((fd = open("test", O_RDONLY)) != -1)
	{
		if (get_next_line(fd, &str))
			printf("|%s|\n", str);
		if (get_next_line(fd, &str))
			printf("|%s|\n", str);
	}
	return (0);
}
