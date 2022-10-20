/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:34:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/08/29 17:43:58 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	num_order(int n);
static int	ten_pow(int c);
static char	*specials(int c);
static char	*str_result(int pow, int i, char *result, int n);

char	*ft_itoa(int n)
{
	int		i;
	char	*result;
	int		pow;

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

static char	*str_result(int pow, int i, char *result, int n)
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

static int	num_order(int n)
{
	int	i;

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

static int	ten_pow(int c)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (i < (c - 1))
	{
		result *= 10;
		i++;
	}
	return (result);
}

static char	*specials(int c)
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
