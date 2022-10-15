/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:11:25 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 08:52:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		write(1, "\0", 1);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
