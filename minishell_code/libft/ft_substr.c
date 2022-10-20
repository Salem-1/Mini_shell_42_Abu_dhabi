/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:29:41 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/22 15:13:43 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	end;
	unsigned int	i;
	char			*result;

	if (len > (size_t)ft_strlen(s))
		len = (size_t)ft_strlen(s);
	result = (char *)ft_calloc(1, len + 1);
	if (!result)
		return (NULL);
	end = start + len;
	i = start;
	if ((start > (unsigned int) ft_strlen(s)) || len == 0)
	{
		result[0] = '\0';
		return (result);
	}
	while (i < end && s[i])
	{
		result[i - start] = s[i];
		i++;
	}
	result[i - start] = '\0';
	return (result);
}
