/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_str_join.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 06:49:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/12 08:22:43 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
static void	init_args(size_t *tmp_len, size_t * reader_len, char *tmp, char *reader);
//first argument will be freed, but always first string will be copied
char	*expand_strjoin(char *tmp, char *reader)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	tmp_len;
	size_t		reader_len;

	init_args(&tmp_len, &reader_len, tmp, reader);
	new = NULL;
	new = malloc(reader_len +  tmp_len + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	tmp_len = ft_strlen(tmp);
	printf("tmp before cpy\n");
	while (++i < tmp_len)
		new[i] = tmp[i];
	i--;
	printf("new before last join\n");
	while (++i < tmp_len + reader_len)
		new[i] = reader[++j];
	new[i] = '\0';
	printf("new before return\n");
	if (tmp)
		free(tmp);
	return (new);
}

void	init_args(
	size_t *tmp_len, size_t * reader_len, char *tmp, char *reader)
{
	*tmp_len = ft_strlen(tmp);
	*reader_len = ft_strlen(reader);
}
