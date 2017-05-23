/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/05/23 18:47:23 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	//static t_list	*catalog = NULL;
	//t_list			*cur;
	static char			*buf;
	char				*tmp;
	ssize_t				ret;

	if (!buf)
		buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buf || !line || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	// get_fd
	if (*line)
		ft_strclr(*line);
	ret = 1;
	tmp = ft_strdup(buf);
	while (!ft_strchr(tmp, '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
		tmp = ft_strappend(&tmp, (char **)&buf, 'F');
	if (ret == -1)
		return (-1);
	if (ft_strchr(tmp, '\n'))
		*line = ft_strsub(tmp, 0, (size_t)(ft_strchr(tmp, '\n') - tmp));
	ft_strclr(buf);
	if (ft_strchr(tmp, '\n'))
		ft_strcpy(buf, (ft_strchr(tmp, '\n') + 1));
	return ((ret || ft_strlen(*line)) ? 1 : 0);
}
