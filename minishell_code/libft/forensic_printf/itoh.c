/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 07:53:14 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 13:31:42 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "//forens_printf.h"

static int	num_order(unsigned int n);
static int	sixteen_pow(unsigned int c);
static char	*specials(unsigned int n, int flag);
static char	*str_result(unsigned int pow, char *result,
				unsigned int n, int flag);

char	*fft_itoh(unsigned int n, int flag)
{
	unsigned int	i;
	char			*result;
	unsigned int	temp;
	unsigned int	pow;

	temp = 1;
	i = 0;
	if (n == 0)
		return (specials(n, flag));
	if (flag == 2)
		result = malloc(sizeof(char) * (num_order(n) + 3));
	else
		result = malloc(sizeof(char) * (num_order(n) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	pow = sixteen_pow(num_order(n));
	if (flag == 0)
		return (str_result(pow, result, n, 0));
	else if (flag == 1)
		return (str_result(pow, result, n, 1));
	else
		return (str_result(pow, result, n, 2));
	return (0);
}

static char	*str_result(unsigned int pow, char *result,
	unsigned int n, int flag)
{
	unsigned int	i;

	if (flag == 2)
	{
		result[0] = '0';
		result[1] = 'x';
		i = 2;
		flag = 0;
	}
	else
		i = 0;
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

static int	num_order(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	sixteen_pow(unsigned int c)
{
	unsigned int	i;
	unsigned int	result;

	i = 0;
	result = 1;
	while (i < (c - 1))
	{
		result *= 16;
		i++;
	}
	return (result);
}

static char	*specials(unsigned int n, int flag)
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
