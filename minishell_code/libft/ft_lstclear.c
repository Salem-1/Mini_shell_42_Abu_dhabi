/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:44:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/18 07:08:03 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*del_me;

	if (!lst)
		return ;
	tmp = *(lst);
	while (tmp)
	{
		del_me = tmp;
		tmp = tmp->next;
		ft_lstdelone(del_me, del);
	}
	*lst = NULL;
}
