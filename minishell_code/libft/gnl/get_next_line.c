/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:13:00 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/06 11:25:02 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	reader[BUFFER_SIZE + 2];
	char		*result;
	int			read_len;

	if (fd < 0 || fd > 10240)
		return (NULL);
	result = NULL;
	if (reader[0])
	{
		result = ft_mystrcpy(result, reader);
		if (result[isnl(result, ln(result) + 1) - 1] == '\0')
			result = f(isnl(result, ln(result) + 1), fd, reader, result);
		result = filler(reader, result, fd);
		return (result);
	}
	else
	{
		read_len = read(fd, reader, BUFFER_SIZE);
		if (read_len == 0 || read_len == -1)
			return (NULL);
		reader[read_len] = '\0';
		result = ft_mystrcpy(result, reader);
		result = filler(reader, result, fd);
		return (result);
	}
}

char	*f(int read_len, int fd, char *reader, char *result)
{
	if (read_len == 0 || read_len == -1)
		return (NULL);
	read_len = read(fd, reader, BUFFER_SIZE);
	reader[read_len] = '\0';
	result = my_strjoin(result, reader, ln(result) + read_len);
	return (result);
}

int	ln(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

void	fill_reader(char *reader, char *tmp)
{
	int	read_len;
	int	len_reader;
	int	counter;

	read_len = isnl(reader, ln(reader)) - 1;
	if (read_len == -2)
		read_len = ln(reader);
	counter = -1;
	tmp = ft_mystrcpy(tmp, reader);
	len_reader = ln(reader);
	null_me(reader);
	while (++read_len < len_reader)
			reader[++counter] = tmp[read_len];
	free(tmp);
}
