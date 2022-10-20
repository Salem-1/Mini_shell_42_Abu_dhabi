/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/29 17:43:26 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*word_data(char const *s, char c, int i);
static int	*word_data_helper(char const *s, int *arr, char c, int j);
static char	**nuller(char **arr);
static int	splitter_core(int *all_data, char **arr, int i, const char *s);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		*all_data;
	int		i;
	int		j;

	arr = NULL;
	if (!*s)
		return (nuller(arr));
	i = 0;
	all_data = word_data(s, c, i);
	if (!all_data)
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *), (all_data[i] + 1));
	if (!arr)
	{
		free(all_data);
		return (NULL);
	}
	i ++;
	j = splitter_core(all_data, arr, i, s);
	free(all_data);
	arr[j] = NULL;
	return (arr);
}

static int	splitter_core(int *all_data, char **arr, int i, const char *s)
{
	int	j;

	j = 0;
	while (j < all_data[0])
	{
		arr[j] = ft_substr(s, all_data[i], (all_data[i + 1] - all_data[i]));
		j++;
		i += 2;
	}
	return (j);
}

static int	*word_data(char const *s, char c, int i)
{
	int	word_counter;
	int	*arr;
	int	j;

	j = 1;
	word_counter = 0;
	if (s[i] != c)
		word_counter++;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1]))
			word_counter++;
		i++;
	}
	arr = ft_calloc(sizeof(int *), (word_counter + 2) + 1);
	if (!arr)
		return (NULL);
	arr[0] = word_counter;
	if (s[0] != c)
	{	
		arr[j] = 0;
		j++;
	}
	return (word_data_helper(s, arr, c, j));
}

static char	**nuller(char **arr)
{
	arr = ft_calloc(sizeof(char *), 1);
	if (!arr)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}

static int	*word_data_helper(const char *s, int *arr, char c, int j)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == c && (s[i + 1] != c) && s[i + 1]))
		{
			arr[j] = i + 1;
			j++;
		}
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
		{
			arr[j] = i + 1;
			j++;
		}
		i++;
	}
	return (arr);
}
