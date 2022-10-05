/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:16:01 by ahsalem           #+#    #+#             */
/*   Updated: 2022/05/31 07:55:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(initial dst) + strlen(src); if retval >= siz,
 * truncation occurred.
 */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = (size_t)ft_strlen(dst);
	if (!dst)
		return (0);
	if (dstsize == 0)
		return ((size_t)ft_strlen(src));
	if (dstsize < (size_t)ft_strlen(dst))
		return (dstsize + (size_t)ft_strlen(src));
	while (((n + i) < dstsize - 1))
	{
		dst[i + n] = src[n];
		if (!src[n])
			break ;
		n++;
	}
	dst[i + n] = '\0';
	return (i + (size_t)ft_strlen(src));
}
