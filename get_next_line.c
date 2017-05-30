/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/05/30 22:48:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

char	**getbuf(const int fd)
{
	static t_list	*catalog = NULL;
	t_list			*cur;
	char			**res;

ft_putendl(">in getbuf");
	if (!catalog)
		catalog = (t_list *)malloc(sizeof(t_list));
	if (!catalog)
		return (NULL);
ft_putendl(">catalog exists");
	cur = catalog;
	while ((int)cur->content_size != fd && cur->next)
		cur = cur->next;
ft_putendl(">out of while");
	if ((int)cur->content_size != fd)
	{
ft_putendl(">NO FD");
		if(!(res = (char **)malloc(sizeof(char *))))
			return (NULL);
		if(!(*res = ft_strnew(BUFF_SIZE)))
			return (NULL);
		ft_lstaddend(&catalog, ft_lstnew((const void *)res, fd));
	}
	else
		res = (char **)cur->content;
ft_putendl(">out getbuf");
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	char				**buf;
	char				*tmp;
	ssize_t				ret;

	buf = getbuf(fd);
	if (!buf || !*buf || !line || fd < 0 || read(fd, *buf, 0) < 0)
		return (-1);
	*line = NULL;
	tmp = ft_strdup(*buf);
	while (!ft_strchr(tmp, '\n') && (ret = read(fd, *buf, BUFF_SIZE)) > 0)
	{
		(*buf)[ret] = '\0';
		tmp = ft_strappend(&tmp, buf, 'F');
	}
	if (ret == -1)
		return (-1);
	*line = ft_strsub(tmp, 0, (ft_strchr(tmp, '\n')) ?
		((size_t)(ft_strchr(tmp, '\n') - tmp)) : ft_strlen(tmp));
	ft_strclr(*buf);
	if (ft_strchr(tmp, '\n'))
		ft_strcpy(*buf, (ft_strchr(tmp, '\n') + 1));
	return ((ret || ft_strlen(*buf) || ft_strlen(*line)) ? 1 : 0);
}
