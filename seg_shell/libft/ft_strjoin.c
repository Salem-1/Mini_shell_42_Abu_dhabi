/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:27:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/05/21 19:37:52 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*joined;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(sizeof(*s1) * total_len + 1);
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, total_len);
	ft_strlcpy(&joined[ft_strlen(s1)], s2, total_len - ft_strlen(s1) + 1);
	return (joined);
}
