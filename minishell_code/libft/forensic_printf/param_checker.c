/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fparam_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:53:17 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 11:31:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "//forens_printf.h"

static int	print_char(char c);
static int	print_string(char *arg);

int	fparam_checker(const char *s, void *arg)
{
	if (*s == 'c')
		return (print_char((char)arg));
	else if (*s == 'i')
		return (fprint_int((int)arg));
	else if (*s == 'd')
		return (fprint_digit((signed int)arg));
	else if (*s == 's')
		return (print_string((char *)arg));
	else if (*s == 'u')
		return (fprint_unsigned((unsigned int)arg));
	else if (*s == 'x')
		return (fprint_hex((unsigned int)arg, 0));
	else if (*s == 'X')
		return (fprint_hex((unsigned int)arg, 1));
	else if (*s == 'p')
		return (fprint_ptr((unsigned long )arg, 2));
	return (0);
}

static int	print_string(char *arg)
{
	if (!arg)
	{
		write(FD, "(null)", 6);
		return (6);
	}
	flocal_ft_putstr_fd(arg, FD);
	return ((int)ft_strlen(arg));
}

static int	print_char(char c)
{
	write(FD, &c, 1);
	return (1);
}

void	flocal_ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
