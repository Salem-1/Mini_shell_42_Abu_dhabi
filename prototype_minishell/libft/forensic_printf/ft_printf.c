/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:13:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 08:56:59 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forens_printf.h"

static int	ft_putchar(const char *s);

static int	print_percent(void)
{
	int	a;

	a = '%';
	write(FD, &a, 1);
	return (1);
}

int	forens_printf(const char *s, ...)
{
	va_list	ptr;
	int		i;
	int		len;
	int		fd;

	fd = open("forensics_cmds.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (!fd)
		return (0);
	dup2(FD, fd);
	i = 0;
	len = 0;
	va_start(ptr, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == '%')
				len += (print_percent());
			else
				len += param_checker(&s[i], va_arg(ptr, void *));
		}
		else
			len += ft_putchar(&s[i]);
		if (!s[i + 1])
			break ;
		i++;
	}
	va_end(ptr);
	close(FD);
	return (len);
}

static int	ft_putchar(const char *s)
{
	write(FD, s, 1);
	return (1);
}
 // ft_forens_printf("Hello %c %c", 'a','d') // Hello a d