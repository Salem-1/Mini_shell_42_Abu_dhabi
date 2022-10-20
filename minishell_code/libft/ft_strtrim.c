/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:28:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/05/31 19:53:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char const *s, char const *set);
static int	starter(const char *s1, const char *set, int flag);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;

	if (set == NULL || !*set)
		return (ft_strdup(s1));
	if (!s1)
		return ("\0");
	start = starter(s1, set, 0);
	end = starter(s1, set, 1);
	if (start > end || start == (int)ft_strlen(s1) -1)
	{
		trimmed = malloc(sizeof(char) * (1));
		if (!trimmed)
			return (NULL);
		*trimmed = '\0';
	}
	else
	{
		trimmed = malloc(sizeof(char) * (end - start + 2));
		if (!trimmed)
			return (NULL);
		ft_strlcpy(trimmed, &s1[start], end - start + 2);
	}
	return (trimmed);
}

static int	check_char(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (*s == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	starter(const char *s1, const char *set, int flag)
{
	int	index;

	if (!flag)
	{
		index = 0;
		while (index < (int)ft_strlen((char *)s1))
		{
			if (!check_char(&s1[index], set))
				break ;
			index++;
		}
	}
	else
	{
		index = (int)ft_strlen(s1) - 1;
		while (index > 0)
		{
			if (!check_char(&s1[index], set))
				break ;
			index--;
		}
	}
	return (index);
}
