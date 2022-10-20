/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:39:55 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/18 07:09:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			del(tmp->content);
			free(tmp);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new, tmp);
	}
	return (new);
}
