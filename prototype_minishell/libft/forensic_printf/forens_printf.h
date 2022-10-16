/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forens_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:17:52 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 11:43:33 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORENS_PRINTF_H
# define FORENS_PRINTF_H
# include "../libft.h"
# include <stdarg.h>

# define FD 3

int		forens_printf(const char *s, ...);
int		fparam_checker(const char *s, void *arg);
int		fprint_int(int n);
int		fprint_digit(signed int n);
int		fprint_unsigned(unsigned int n);
char	*fft_unsigned_itoa(unsigned int n);
char	*fft_signed_itoa(signed int n);
char	*fft_itoh(unsigned int n, int flag);
int		fprint_hex(unsigned int n, int flag);
char	*fft_itop(unsigned long n, int flag);
int		fprint_ptr(unsigned long n, int flag);
void	flocal_ft_putstr_fd(char *s, int fd);

#endif