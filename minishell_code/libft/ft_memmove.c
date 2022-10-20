/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:12:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/06/03 17:35:29 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	forward(size_t i, size_t len, char *s, char *d)
{
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

static void	backward(size_t i, size_t len, char *s, char *d)
{
	i = len - 1;
	while (i > 0)
	{
		d[i] = s[i];
		i--;
	}
	d[0] = s[0];
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	size_t	len;
	char	*d;
	char	*s;

	if (!((char *)dst) && !((char *)src))
		return (dst);
	if (n == 0)
		return (dst);
	len = n;
	d = &*((char *) dst);
	s = &*((char *) src);
	i = 0;
	if (s > d)
		forward(i, len, s, d);
	else
		backward(i, len, s, d);
	return (dst);
}
