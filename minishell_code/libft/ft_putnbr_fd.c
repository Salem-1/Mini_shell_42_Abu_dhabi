/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:04:57 by ahsalem           #+#    #+#             */
/*   Updated: 2022/06/01 20:27:48 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_negative(int n, int fd)
{
	char	holder;

	if (n < 0)
	{
		holder = '-';
		write(fd, &holder, 1);
		n *= -1;
	}
	return (n);
}

int	expo(int n)
{
	int	x;

	x = 1;
	n /= 10;
	while (n > 0)
	{
		n /= 10;
		x *= 10;
	}
	return (x);
}

void	printn(int n, int fd)
{
	char	a;

	a = '0' + n;
	write(fd, &a, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	temp;
	int	result;
	int	x;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	temp = n;
	n = is_negative(temp, fd);
	x = expo(n);
	while (x > 0)
	{
		result = n / x;
		printn(result % 10, fd);
		x /= 10;
	}
}
