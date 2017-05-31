/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/05/31 16:46:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

char	*getbuf(const int fd)
{
	static t_list	*catalog = NULL;
	t_list			*cur;
	char			*res;

	if (!catalog)
		catalog = (t_list *)malloc(sizeof(t_list));
	if (!catalog)
		return (NULL);
	cur = catalog;
	while ((int)cur->content_size - 1 != fd && cur->next)
		cur = cur->next;
	if ((int)cur->content_size - 1 != fd)
	{
		if(!(res = ft_strnew(BUFF_SIZE)))
			return (NULL);
		ft_lstaddend(&catalog, ft_lstnew((const void *)res, fd + 1));
		cur = cur->next;
	}
	res = (char *)cur->content;
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	char				*buf;
	char				*tmp;
	ssize_t				ret;

	buf = getbuf(fd);
	if (!buf || !line || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = NULL;
	tmp = ft_strdup(buf);
	while (!ft_strchr(tmp, '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strappend(&tmp, &buf, 'F');
	}
	if (ret == -1)
	{
		ft_putendl("read error");
		return (-1);
	}
	*line = ft_strsub(tmp, 0, (ft_strchr(tmp, '\n')) ?
		((size_t)(ft_strchr(tmp, '\n') - tmp)) : ft_strlen(tmp));
	ft_strclr(buf);
	if (ft_strchr(tmp, '\n'))
		ft_strcpy(buf, (ft_strchr(tmp, '\n') + 1));
	return ((ret || ft_strlen(buf) || ft_strlen(*line)) ? 1 : 0);
}
