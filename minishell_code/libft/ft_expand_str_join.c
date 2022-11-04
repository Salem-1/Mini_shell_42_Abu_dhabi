/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_str_join.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 06:49:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/04 08:47:46 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_expand_strjoin(char *s1, char *s2)
{
	int		total_len;
	char	*joined;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(sizeof(*s1) * total_len + 1);
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, total_len);
	ft_strlcpy(&joined[ft_strlen(s1)], s2, total_len - ft_strlen(s1) + 1);
	if (s1)
		free(s1);
	if(s2)
		free(s2);
	return (joined);
}

