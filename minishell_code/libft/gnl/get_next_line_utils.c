/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:11:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/14 11:19:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_mystrcpy(char *result, char *reader)
{
	int	i;

	i = -1;
	result = malloc(sizeof(char *) * ln(reader) + 2);
	if (!result)
		return (NULL);
	while (reader[++i])
		result[i] = reader[i];
	result[i] = '\0';
	result[++i] = '\0';
	return (result);
}

char	*my_strjoin(char *tmp, char *reader, int counter)
{
	char	*new;
	int		i;
	int		j;
	int		reader_len;

	new = NULL;
	new = malloc(counter + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	reader_len = ln(reader);
	while (++i < counter - reader_len)
		new[i] = tmp[i];
	i--;
	while (++i < counter)
		new[i] = reader[++j];
	new[i] = '\0';
	free(tmp);
	return (new);
}

int	isnl(char *tmp, int counter)
{
	int	i;

	if (tmp == NULL)
		return (1);
	i = -1;
	while (++i < counter)
	{
		if (tmp[i] == '\n' || tmp[i] == '\0')
			return (++i);
	}
	return (-1);
}

char	*filler(char *reader, char *result, int fd)
{
	int		read_len;
	int		counter;
	char	*tmp;

	tmp = NULL;
	counter = ln(result);
	read_len = 0;
	while (isnl(reader, BUFFER_SIZE) == -1)
	{
		read_len = read(fd, reader, BUFFER_SIZE);
		reader[read_len] = '\0';
		counter += read_len;
		result = my_strjoin(result, reader, counter);
	}
	if (isnl(result, counter) != -1)
		result[isnl(result, counter)] = '\0';
	if (reader[0] != '\0')
		fill_reader(reader, tmp);
	return (result);
}

void	null_me(char *reader)
{
	int	i;

	i = -1;
	while (reader[++i])
		reader[i] = '\0';
}
