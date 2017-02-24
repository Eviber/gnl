/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:57:39 by ygaude            #+#    #+#             */
/*   Updated: 2017/02/24 17:40:49 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int		main(void)
{
	char	*line = NULL;
	int		fd = open("gnl10.txt", O_RDONLY);

	get_next_line(fd, &line);
	close(fd);
	return (0);
}
