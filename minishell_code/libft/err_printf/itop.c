/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 07:53:14 by ahsalem           #+#    #+#             */
/*   Updated: 2022/06/06 21:12:52 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				num_order(unsigned long n);
static unsigned long	sixteen_pow(unsigned long c);
static char				*specials(unsigned long n, int flag);
static char				*str_result(unsigned long pow, char *result,
							unsigned long n, int flag);

char	*ft_itop(unsigned long n, int flag)
{
	unsigned long	i;
	char			*result;
	unsigned long	temp;
	unsigned long	pow;

	temp = 1;
	i = 0;
	if (n == 0)
		return (specials(n, flag));
	result = malloc(sizeof(char) * (num_order(n) + 3));
	if (result == NULL)
		return (NULL);
	i = 0;
	pow = sixteen_pow(num_order(n));
	return (str_result(pow, result, n, 2));
}

static char	*str_result(unsigned long pow, char *result,
	unsigned long n, int flag)
{
	unsigned long	i;

	result[0] = '0';
	result[1] = 'x';
	i = 2;
	flag = 0;
	while (pow > 0)
	{
		result[i] = n / pow % 16;
		if (result[i] < 10)
			result[i] += '0';
		else if (flag == 0)
			result[i] += 87;
		else
			result[i] += 55;
		pow /= 16;
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	num_order(unsigned long n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static unsigned long	sixteen_pow(unsigned long c)
{
	unsigned long	i;
	unsigned long	result;

	i = 0;
	result = 1;
	while (i < (c - 1))
	{
		result *= 16;
		i++;
	}
	return (result);
}

static char	*specials(unsigned long n, int flag)
{
	char	*result;

	if (n == 0 && flag == 2)
	{
		result = ft_strdup("0x0");
		return (result);
	}
	if (n == 0)
		result = ft_strdup("0");
	else
		result = ft_strdup("ffffffff");
	return (result);
}
