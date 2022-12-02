/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polymorophic_itoa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:15:55 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 14:55:36 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forens_printf.h"

int	num_order(int n);

int	fprint_hex(unsigned int n, int flag)
{
	int		len;
	char	*result;

	result = fft_itoh(n, flag);
	flocal_ft_putstr_fd(result, FD);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	fprint_ptr(unsigned long n, int flag)
{
	int		len;
	char	*result;

	result = fft_itop(n, flag);
	flocal_ft_putstr_fd(result, FD);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	fprint_unsigned(unsigned int n)
{
	char	*result;
	int		len;

	result = fft_unsigned_itoa(n);
	flocal_ft_putstr_fd(result, FD);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	fprint_int(int n)
{
	char	*result;
	int		len;

	result = ft_itoa(n);
	flocal_ft_putstr_fd(result, FD);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}

int	fprint_digit(signed int n)
{
	char	*result;
	int		len;

	result = fft_signed_itoa(n);
	flocal_ft_putstr_fd(result, FD);
	len = (int)ft_strlen(result);
	free(result);
	return (len);
}
