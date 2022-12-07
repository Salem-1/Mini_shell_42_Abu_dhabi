/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:37:18 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/21 09:11:22 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(const char *c);
long	int_generator(const char *str, long num, int sign);

long	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign *= -1;
			str++;
			break ;
		}
		else if (*str >= '0' && *str <= '9')
			break ;
		else if (ft_isspace(str))
		{
			str++;
			continue ;
		}
		else
			return (0);
	}
	return (int_generator(str, num, sign));
}

int	ft_isspace(const char *c)
{
	if ((*c >= 9 && *c <= 13) || *c == 32)
		return (1);
	else
		return (0);
}

long	int_generator(const char *str, long num, int sign)
{
	int	outliar;

	outliar = 0;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
		outliar++;
	}
	if (outliar > 18)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (num * sign);
}
