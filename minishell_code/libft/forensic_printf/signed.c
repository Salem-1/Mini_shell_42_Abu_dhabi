/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 22:47:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 13:31:42 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "//forens_printf.h"

static signed int	num_order(signed int n);
static signed int	ten_pow(signed int c);
static char			*specials(signed int c);
static char			*str_result(signed int pow,
						signed int i, char *result, signed int n);

char	*fft_signed_itoa(signed int n)
{
	signed int		i;
	char			*result;
	signed int		temp;
	signed int		pow;

	temp = 1;
	i = 0;
	if (n == 0 || n == -2147483648)
		return (specials(n));
	result = malloc(sizeof(char) * (num_order(n) + 1));
	if (result == NULL)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
		i = 1;
	}
	else
		i = 0;
	pow = ten_pow(num_order(n));
	return (str_result(pow, i, result, n));
}

static char	*str_result(signed int pow,
			signed int i, char *result, signed int n)
{
	while (pow > 0)
	{
		result[i] = n / pow % 10 + '0';
		pow /= 10;
		i++;
	}
	result[i] = '\0';
	return (result);
}

static signed int	num_order(signed int n)
{
	signed int	i;

	if (n < 0)
	{
		n *= -1;
		i = 1;
	}
	else
		i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static signed int	ten_pow(signed int c)
{
	signed int	i;
	signed int	result;

	i = 0;
	result = 1;
	while (i < (c - 1))
	{
		result *= 10;
		i++;
	}
	return (result);
}

static char	*specials(signed int c)
{
	char	*result;

	if (c == 0)
	{
		result = (char *)malloc(sizeof(char ) * 2);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		result = malloc(sizeof(char) * 12);
		ft_strlcpy(result, "-2147483648", 12);
	}
	return (result);
}
