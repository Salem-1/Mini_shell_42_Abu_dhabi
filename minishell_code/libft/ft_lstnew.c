/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 08:13:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/25 22:03:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **content)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list) ,  1);
	if (!new)
		return (NULL);
	new->content = NULL;
	new->key_val = content;
	new->flag = 'v';
	new->next = NULL;
	return (new);
}
