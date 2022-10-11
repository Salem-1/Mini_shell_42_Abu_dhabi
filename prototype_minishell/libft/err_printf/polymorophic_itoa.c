/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polymorophic_itoa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:15:55 by ahsalem           #+#    #+#             */
/*   Updated: 2022/06/06 16:39:41 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	num_order(int n);

int	print_hex(unsigned int n, int flag)
{
	int		len;
	char	*result;

	result = ft_itoh(n, flag);
	ft_putstr(result);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	print_ptr(unsigned long n, int flag)
{
	int		len;
	char	*result;

	result = ft_itop(n, flag);
	ft_putstr(result);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	print_unsigned(unsigned int n)
{
	char	*result;
	int		len;

	result = ft_unsigned_itoa(n);
	ft_putstr(result);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	print_int(int n)
{
	char	*result;
	int		len;

	result = ft_itoa(n);
	ft_putstr(result);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	print_digit(signed int n)
{
	char	*result;
	int		len;

	result = ft_signed_itoa(n);
	ft_putstr(result);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}
