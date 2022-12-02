/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:13:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 14:52:10 by ahsalem          ###   ########.fr       */
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

int	looping_thorw_string(const char *s, va_list *ptr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == '%')
				len += (print_percent());
			else
				len += fparam_checker(&s[i], va_arg(*ptr, void *));
		}
		else
			len += ft_putchar(&s[i]);
		if (!s[i + 1])
			break ;
		i++;
	}
	return (len);
}

int	forens_printf(const char *s, ...)
{
	va_list	ptr;
	int		fd;
	int		len;

	len = 0;
	fd = open("forensics_cmds.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (0);
	dup2(FD, fd);
	va_start(ptr, s);
	len = looping_thorw_string(s, &ptr);
	va_end(ptr);
	close(FD);
	return (len);
}

static int	ft_putchar(const char *s)
{
	write(FD, s, 1);
	return (1);
}
