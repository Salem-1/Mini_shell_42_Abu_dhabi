/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:25:26 by ahsalem           #+#    #+#             */
/*   Updated: 2022/05/17 09:02:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *)(haystack));
	while (i < len && haystack[i])
	{
		if (len - i < (size_t)ft_strlen(needle))
			return (0);
		if (!ft_strncmp(haystack + i, needle, (size_t)ft_strlen(needle)))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
