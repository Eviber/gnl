/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 12:52:57 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/12 17:28:05 by ygaude           ###   ########.fr       */
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

int		get_next_line(const int fd, char **line)
{
	ssize_t		len;
	static char	*buf = NULL;
	char		*tmp;

	*line = ft_strnew(1);
	tmp = NULL;
	len = 0;
	if (!buf)
		buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	else
		*line = ft_strappend(*line, buf);
	while (buf && !tmp && (len = read(fd, buf, BUFF_SIZE)) && len != -1)
	{
		tmp = ft_strchr(buf, '\n');
		*line = ft_strappend(*line, buf);
		buf[len] = '\0';
	}
	if (len == -1)
		return (-1);
	if (!len && !tmp)
		return (0);
	ft_memmove(buf, tmp + 1, ft_strlen(tmp));
	tmp = ft_strchr(*line, '\n');
	if (tmp)
		*tmp = '\0';
	return (1);
}

int		main(void)
{
	int		fd;
	int		res;
	char	*str;

	if ((fd = open("test", O_RDONLY)) != -1)
	{
		while ((res = get_next_line(fd, &str)) && res != -1)
			printf("|%s|\n", str);
	}
	return (0);
}
