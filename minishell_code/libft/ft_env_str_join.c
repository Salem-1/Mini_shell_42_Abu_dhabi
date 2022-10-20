/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_str_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 06:49:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/12 07:58:12 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//first argument will be freed
char	*env_strjoin(char *tmp, char *reader, size_t counter)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	reader_len;

	new = NULL;
	new = malloc(counter + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	reader_len = ft_strlen(reader);
	while (++i < counter - reader_len)
		new[i] = tmp[i];
	i--;
	while (++i < counter)
		new[i] = reader[++j];
	new[i] = '\0';
	if (tmp)
		free(tmp);
	return (new);
}