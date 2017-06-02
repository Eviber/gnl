/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelthis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 15:21:57 by ygaude            #+#    #+#             */
/*   Updated: 2017/06/02 16:13:05 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelthis(t_list **alst, t_list *target)
{
	t_list	*cur;
	t_list	*tmp;

ft_putendl("DELTHIS");
	if (!alst || !*alst || !target)
		return ;
	cur = *alst;
	tmp = cur;
	if (cur == target)
		*alst = cur->next;
	while (cur && cur->next && cur->next != target && cur != target)
		cur = cur->next;
	if (cur->next == target)
	{
		tmp = cur->next;
		cur->next = tmp->next;
	}
	else if (cur != target)
		return ;
	ft_memdel(&(tmp->content));
	ft_memdel((void *)&tmp);
}
