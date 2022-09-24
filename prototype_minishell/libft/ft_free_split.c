/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:21:06 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/22 21:21:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **splited)
{
	int	i;

	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
}
