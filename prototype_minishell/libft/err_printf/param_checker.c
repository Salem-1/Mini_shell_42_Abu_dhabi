/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:53:17 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 19:11:47 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_char(char c);
static int	print_string(char *arg);

int	param_checker(const char *s, void *arg)
{
	if (*s == 'c')
		return (print_char((char)arg));
	else if (*s == 'i')
		return (print_int((int)arg));
	else if (*s == 'd')
		return (print_digit((signed int)arg));
	else if (*s == 's')
		return (print_string((char *)arg));
	else if (*s == 'u')
		return (print_unsigned((unsigned int)arg));
	else if (*s == 'x')
		return (print_hex((unsigned int)arg, 0));
	else if (*s == 'X')
		return (print_hex((unsigned int)arg, 1));
	else if (*s == 'p')
		return (print_ptr((unsigned long )arg, 2));
	return (0);
}

static int	print_string(char *arg)
{
	if (!arg)
	{
		write(2, "(null)", 6);
		return (6);
	}
	ft_putstr(arg);
	return ((int)ft_strlen(arg));
}

static int	print_char(char c)
{
	write(2, &c, 1);
	return (1);
}
